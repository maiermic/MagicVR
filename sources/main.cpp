#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "inVRs/SystemCore/DebugOutput.h"
#include "magicvr/MagicVrApp.hpp"

OSG_USING_NAMESPACE

int main(int argc, char **argv) {
#if WIN32
    OSG::preloadSharedObject("OSGFileIO");
    OSG::preloadSharedObject("OSGImageFileIO");
#endif
    MagicVrApp app;
    if (!app.start(argc, argv)) {
        printd(ERROR, "Error occured during startup!\n");
        return -1;
    }
}
