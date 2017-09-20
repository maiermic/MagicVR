#include <inVRs/SystemCore/DebugOutput.h>
#include <Scene.hpp>
#include <input/RemoteManager.hpp>
#include "MagicVrApp.hpp"

std::string MagicVrApp::getConfigFile(const CommandLineArgumentWrapper &args) {
    return args.containOption("config") ? args.getOptionValue("config") : defaultConfigFile;
}

bool MagicVrApp::initialize(const CommandLineArgumentWrapper &args) {
    OpenSGSceneGraphInterface* sgIF =
            dynamic_cast<OpenSGSceneGraphInterface*>(sceneGraphInterface);
    // must exist because it is created by the OutputInterface
    if (!sgIF) {
        printd(ERROR, "GoingImmersive::initialize(): Unable to obtain SceneGraphInterface!\n");
        return false;
    } // if

    // obtain the scene node from the SceneGraphInterface
//    OSG::NodeRecPtr scene = sgIF->getNodePtr();

    // TODO build scene without cfg
    OSGCSM::CAVEConfig cfg;
    input::RemoteManager remoteManager(cfg);
    Scene scene(remoteManager.wand);

    // set root node to the responsible SceneManager (managed by OpenSGApplicationBase)
//    setRootNode(scene);
    setRootNode(scene.root);

    return true;
}

void MagicVrApp::display(float dt) {

}

void MagicVrApp::cleanup() {

}

MagicVrApp::MagicVrApp() : defaultConfigFile("config/general.xml") {}

MagicVrApp::~MagicVrApp() {
    globalCleanup();
}

