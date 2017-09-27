#include <stdio.h>
#include <magicvr/ExitGlut.hpp>
#include <magicvr/AppController.hpp>
#include "magicvr/MagicVrDesktopGlutFramework.hpp"


OSG_USING_NAMESPACE

int main(int argc, char **argv) {
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
    // ChangeList needs to be set for OpenSG 1.4
    ChangeList::setReadWriteDefault();
    osgInit(argc, argv);

    try {
        AppController app;
        MagicVrDesktopGlutFramework framework(app);
        framework.startFramework(argc, argv);
    } catch (const ExitGlut& e) {
        std::cout << "clean exit of app\n";
    }
}
