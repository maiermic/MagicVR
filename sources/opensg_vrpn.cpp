#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <iostream>
#include <ios>

#include <OpenSG/OSGGLUT.h>
#include <OpenSG/OSGConfig.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGMultiDisplayWindow.h>
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGSwitch.h>

#include <OSGCSM/OSGCAVESceneManager.h>
#include <OSGCSM/OSGCAVEConfig.h>
#include <OSGCSM/appctrl.h>

#include "Arguments.h"
#include "Scene.h"
#include "input/RemoteManager.h"

OSG_USING_NAMESPACE

OSGCSM::CAVEConfig cfg;
OSGCSM::CAVESceneManager *mgr = nullptr;

input::RemoteManager *remoteManager;

Scene *scene = nullptr;

// head light fix (1/3)
DirectionalLightRecPtr mainLight;

void cleanup() {
    delete mgr;
    delete remoteManager;
}

void keyboard(unsigned char k, int x, int y) {
    Real32 ed;
    switch (k) {
        case 'q':
        case 27:
            cleanup();
            exit(EXIT_SUCCESS);
            break;
        case 'e':
            ed = mgr->getEyeSeparation() * .9f;
            std::cout << "Eye distance: " << ed << '\n';
            mgr->setEyeSeparation(ed);
            break;
        case 'E':
            ed = mgr->getEyeSeparation() * 1.1f;
            std::cout << "Eye distance: " << ed << '\n';
            mgr->setEyeSeparation(ed);
            break;
        case 'h':
            cfg.setFollowHead(!cfg.getFollowHead());
            std::cout << "following head: " << std::boolalpha << cfg.getFollowHead() << '\n';
            break;
        case 'i':
            remoteManager->print_tracker();
            break;
        default:
            std::cout << "Key '" << k << "' ignored\n";
    }
}

void setupGLUT(int *argc, char *argv[]) {
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("OpenSG CSMDemo with VRPN API");
    glutDisplayFunc([]() {
        // black navigation window
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
    });
    glutReshapeFunc([](int w, int h) {
        mgr->resize(w, h);
        glutPostRedisplay();
    });
    glutKeyboardFunc(keyboard);
    glutIdleFunc([]() {
        remoteManager->check_tracker();

        scene->update();

        const auto speed = 1.f;
        auto head = remoteManager->head;
        mgr->setUserTransform(head.position, head.orientation);
        mgr->setTranslation(mgr->getTranslation() + speed * remoteManager->analog_values);

        // head light fix (2/3)
        Matrix4f mat;
        mat.setRotate(head.orientation);
        auto dir = mat * Vec3f(0.f, 0.f, 1.f);
        mainLight->setDirection(dir);

        commitChanges();
        mgr->redraw();
        // the changelist should be cleared - else things could be copied multiple times
        OSG::Thread::getCurrentChangeList()->clear();
    });
}

int main(int argc, char **argv) {
#if WIN32
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
#endif
    try {
        // ChangeList needs to be set for OpenSG 1.4
        ChangeList::setReadWriteDefault();
        osgInit(argc, argv);

        // evaluate intial params
        Arguments args(argc, argv);

        if (args.configurationFile == nullptr) {
            throw "No configuration passed.";
        } else if (!cfg.loadFile(args.configurationFile)) {
            std::string file = args.configurationFile;
            throw "ERROR: could not load config file '" + file + "'";
        }

        cfg.printConfig();

        // start servers for video rendering
        if (startServers(cfg) < 0) {
            std::cout << "ERROR: Failed to start servers\n";
            return EXIT_FAILURE;
        }

        setupGLUT(&argc, argv);

        remoteManager = new input::RemoteManager(cfg);

        MultiDisplayWindowRefPtr mwin = createAppWindow(cfg, cfg.getBroadcastaddress());

        NodeRefPtr root = nullptr;
        if (args.sceneFile != nullptr) {
            root = SceneFileHandler::the()->read(args.sceneFile, NULL);
            if (!root) {
                throw "Scene could not be loaded: '" + std::string(args.sceneFile) + "'";
            }
        } else {
            scene = new Scene(remoteManager->wand);
            root = scene->root;
        }

        // head light fix (3/3)
        mainLight = DirectionalLight::create();
        mainLight->setDiffuse(Color4f(1, 1, 1, 1));
        mainLight->setAmbient(Color4f(0.2, 0.2, 0.2, 1));
        mainLight->setSpecular(Color4f(1, 1, 1, 1));
        root->setCore(mainLight);
        NodeRecPtr beaconGeo = makeNodeFor(Geometry::create());
        mainLight->setBeacon(beaconGeo);

        commitChanges();

        mgr = new OSGCSM::CAVESceneManager(&cfg);
        mgr->setWindow(mwin);
        mgr->setRoot(root);
        mgr->showAll();
        mgr->getWindow()->init();
        mgr->turnWandOff();
        mgr->setHeadlight(false);
    }
    catch (std::string e) {
        std::cout << "ERROR: " << e << '\n';
        return EXIT_FAILURE;
    }
    catch (const char *e) {
        std::cout << "ERROR: " << e << '\n';
        return EXIT_FAILURE;
    }
    catch (const std::exception &e) {
        std::cout << "ERROR: " << e.what() << '\n';
        return EXIT_FAILURE;
    }

    glutMainLoop();
}
