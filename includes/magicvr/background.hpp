#ifndef MAGICVR_BACKGROUND_HPP
#define MAGICVR_BACKGROUND_HPP

#include <OpenSG/OSGSkyBackground.h>

enum Resolutions {
//    SKYBOX_RES_256 = 256,
//    SKYBOX_RES_512 = 512,
    SKYBOX_RES_1024 = 1024,
    SKYBOX_RES_2048 = 2048
};

OSG::SkyBackgroundUnrecPtr loadBackground(Resolutions skyboxResolution);


#endif //MAGICVR_BACKGROUND_HPP
