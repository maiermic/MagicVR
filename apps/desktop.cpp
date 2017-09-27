#include "Scene.hpp"
#include "magicvr/MagicVrDesktopGlutFramework.hpp"


OSG_USING_NAMESPACE

int main(int argc, char **argv) {
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    // ChangeList needs to be set for OpenSG 1.4
    ChangeList::setReadWriteDefault();
    osgInit(argc, argv);

    input::Tracker wand; // TODO replace with alternative input device
    Scene scene(wand);
    MagicVrDesktopGlutFramework framework(scene);
    framework.startFramework(argc, argv);
}
