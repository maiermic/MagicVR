#include <inVRs/SystemCore/DebugOutput.h>
#include <Scene.hpp>
#include <input/RemoteManager.hpp>
#include "MagicVrApp.hpp"

std::string MagicVrApp::getConfigFile(const CommandLineArgumentWrapper &args) {
    return args.containOption("config") ? args.getOptionValue("config") : defaultConfigFile;
}

bool MagicVrApp::initialize(const CommandLineArgumentWrapper &args) {
    OpenSGSceneGraphInterface *sgIF =
            dynamic_cast<OpenSGSceneGraphInterface *>(sceneGraphInterface);
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

    // head light fix (3/3)
    mainLight = DirectionalLightBase::create();
    mainLight->setDiffuse(Color4f(1, 1, 1, 1));
    mainLight->setAmbient(Color4f(0.2, 0.2, 0.2, 1));
    mainLight->setSpecular(Color4f(1, 1, 1, 1));
    scene.root->setCore(mainLight);
    NodeRecPtr beaconGeo = makeNodeFor(Geometry::create());
    mainLight->setBeacon(beaconGeo);

    commitChanges();

    // set root node to the responsible SceneManager (managed by OpenSGApplicationBase)
//    setRootNode(scene);
    setRootNode(scene.root);

    return true;
}

void MagicVrApp::display(float dt) {
    // TODO get head orientation
    Quaternion head_orientation(Vec3f(0.f, 1.f, 0.f), 3.141f);
    // head light fix (2/3)
    Matrix4f mat;
    mat.setRotate(head_orientation);
    auto dir = mat * Vec3f(0.f, 0.f, 1.f);
    mainLight->setDirection(dir);
}

void MagicVrApp::cleanup() {

}

MagicVrApp::MagicVrApp() : defaultConfigFile("config/general.xml") {}

MagicVrApp::~MagicVrApp() {
    globalCleanup();
}

