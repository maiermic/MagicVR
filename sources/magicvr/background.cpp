#include "magicvr/background.hpp"
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGTextureObjChunk.h>

OSG::SkyBackgroundUnrecPtr loadBackground() {
    OSG::ImageUnrecPtr           imgFront  = OSG::ImageFileHandler::the()->read("models/skybox/envMap_cube_hr_Front.png");
    OSG::TextureObjChunkUnrecPtr texFront  = OSG::TextureObjChunk::create();
    texFront->setImage(imgFront);

    OSG::ImageUnrecPtr           imgBack   = OSG::ImageFileHandler::the()->read("models/skybox/envMap_cube_hr_Back.png");
    OSG::TextureObjChunkUnrecPtr texBack   = OSG::TextureObjChunk::create();
    texBack->setImage(imgBack);

    OSG::ImageUnrecPtr           imgLeft   = OSG::ImageFileHandler::the()->read("models/skybox/envMap_cube_hr_Left.png");
    OSG::TextureObjChunkUnrecPtr texLeft   = OSG::TextureObjChunk::create();
    texLeft->setImage(imgLeft);

    OSG::ImageUnrecPtr           imgRight  = OSG::ImageFileHandler::the()->read("models/skybox/envMap_cube_hr_Right.png");
    OSG::TextureObjChunkUnrecPtr texRight  = OSG::TextureObjChunk::create();
    texRight->setImage(imgRight);

    OSG::ImageUnrecPtr           imgTop    = OSG::ImageFileHandler::the()->read("models/skybox/envMap_cube_hr_Top.png");
    OSG::TextureObjChunkUnrecPtr texTop    = OSG::TextureObjChunk::create();
    texTop->setImage(imgTop);

    OSG::ImageUnrecPtr           imgBottom = OSG::ImageFileHandler::the()->read("models/skybox/envMap_cube_hr_Bottom.png");
    OSG::TextureObjChunkUnrecPtr texBottom = OSG::TextureObjChunk::create();
    texBottom->setImage(imgBottom);

    OSG::SkyBackgroundUnrecPtr skyBG = OSG::SkyBackground::create();
    skyBG->setFrontTexture (texFront);
    skyBG->setBackTexture  (texBack );
    skyBG->setLeftTexture  (texLeft );
    skyBG->setRightTexture (texRight);
    skyBG->setTopTexture   (texTop  );
    skyBG->setBottomTexture(texBottom);

    return skyBG;
}
