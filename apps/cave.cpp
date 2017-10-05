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
#include <magicvr/ExitGlut.hpp>
#include <magicvr/background.hpp>

#include "Arguments.hpp"
#include <magicvr/AppController.hpp>
#include <magicvr/AppControllerWithWandSupport.hpp>
#include "input/RemoteManager.hpp"
#include "magicvr/MagicVrCaveGlutFramework.hpp"

OSG_USING_NAMESPACE

int main(int argc, char **argv) {
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    try {
        // ChangeList needs to be set for OpenSG 1.4
        ChangeList::setReadWriteDefault();
        osgInit(argc, argv);

        // evaluate intial params
        Arguments args(argc, argv);
        OSGCSM::CAVEConfig cfg;

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

        input::RemoteManager remoteManager(cfg);
        magicvr::AppControllerWithWandSupport app(remoteManager);

        MultiDisplayWindowRefPtr mwin = createAppWindow(cfg, cfg.getBroadcastaddress());

        NodeRefPtr root = nullptr;
        if (args.sceneFile != nullptr) {
            root = SceneFileHandler::the()->read(args.sceneFile, NULL);
            if (!root) {
                throw "Scene could not be loaded: '" + std::string(args.sceneFile) + "'";
            }
        } else {
            root = app.root();
        }

        // head light fix (3/3)
        DirectionalLightRecPtr mainLight = DirectionalLightBase::create();
        mainLight->setDiffuse(Color4f(1, 0.3, 0.2, 1));
        mainLight->setAmbient(Color4f(0,0,0,0));
        mainLight->setSpecular(Color4f(0,0,0,0));

        Matrix4f mat;
        mat.setRotate(Quaternion(Vec3f(1,0,0),osgDegree2Rad(20)) * Quaternion(Vec3f(0,1,0),osgDegree2Rad(90)));
        auto dir = mat * Vec3f(0.f, 0.f, 1.f);
        mainLight->setDirection(dir);
        
        root->setCore(mainLight);
        NodeRecPtr beaconGeo = makeNodeFor(Geometry::create());
        mainLight->setBeacon(beaconGeo);

        commitChanges();

        OSGCSM::CAVESceneManager mgr(&cfg);
        mgr.setWindow(mwin);
        mgr.setRoot(root);
        mgr.showAll();
        mgr.getWindow()->init();
        mgr.turnWandOff();
        mgr.setHeadlight(false);
        std::cout << "number of active walls: "
                  << cfg.getNumActiveWalls()
                  << '\n';
        auto bg = loadBackground(SKYBOX_RES_1024);
        for (int i = 0; i < cfg.getNumActiveWalls(); i++) {
            mgr.setBackground(i, bg);
        }

        MagicVrCaveGlutFramework framework(cfg, mgr, remoteManager, app, mainLight);
        framework.startFramework(argc, argv);
    }
    catch (std::string e) {
        std::cout << "ERROR: " << e << '\n';
        return EXIT_FAILURE;
    }
    catch (const char *e) {
        std::cout << "ERROR: " << e << '\n';
        return EXIT_FAILURE;
    }
    catch (const ExitGlut &e) {
        std::cout << "clean exit of app\n";
    }
    catch (const std::exception &e) {
        std::cout << "ERROR: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}
