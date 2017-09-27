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
#include "Scene.hpp"
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
        Scene scene;

        MultiDisplayWindowRefPtr mwin = createAppWindow(cfg, cfg.getBroadcastaddress());

        NodeRefPtr root = nullptr;
        if (args.sceneFile != nullptr) {
            root = SceneFileHandler::the()->read(args.sceneFile, NULL);
            if (!root) {
                throw "Scene could not be loaded: '" + std::string(args.sceneFile) + "'";
            }
        } else {
            root = scene.root();
        }

        // head light fix (3/3)
        DirectionalLightRecPtr mainLight = DirectionalLight::create();
        mainLight->setDiffuse(Color4f(1, 1, 1, 1));
        mainLight->setAmbient(Color4f(0.2, 0.2, 0.2, 1));
        mainLight->setSpecular(Color4f(1, 1, 1, 1));
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
        mgr.setBackground(0, loadBackground());

        MagicVrCaveGlutFramework framework(cfg, mgr, remoteManager, scene, mainLight);
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
