#include "magicvr/background.hpp"
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include "PathSettings.hpp"

OSG::SkyBackgroundUnrecPtr loadBackground(Resolutions skyboxResolution) {
    std::string resolution = std::to_string((int) skyboxResolution);
    std::cout << "skyboxResolution: " << skyboxResolution << std::endl;

    std::string filePathBase = Path_Skybox_Root + resolution + Path_Skybox_Prefix + resolution;

    std::string frontPath = filePathBase + Path_Skybox_Front + Path_Skybox_Suffix;
    std::string backPath = filePathBase + Path_Skybox_Back + Path_Skybox_Suffix;
    std::string leftPath = filePathBase + Path_Skybox_Left + Path_Skybox_Suffix;
    std::string rightPath = filePathBase + Path_Skybox_Right + Path_Skybox_Suffix;
    std::string topPath = filePathBase + Path_Skybox_Top + Path_Skybox_Suffix;
    std::string bottomPath = filePathBase + Path_Skybox_Bottom + Path_Skybox_Suffix;

    OSG::ImageUnrecPtr imgFront = OSG::ImageFileHandler::the()->read(frontPath.c_str());
    OSG::TextureObjChunkUnrecPtr texFront = OSG::TextureObjChunk::create();
    texFront->setImage(imgFront);

    OSG::ImageUnrecPtr imgBack = OSG::ImageFileHandler::the()->read(backPath.c_str());
    OSG::TextureObjChunkUnrecPtr texBack = OSG::TextureObjChunk::create();
    texBack->setImage(imgBack);

    OSG::ImageUnrecPtr imgLeft = OSG::ImageFileHandler::the()->read(leftPath.c_str());
    OSG::TextureObjChunkUnrecPtr texLeft = OSG::TextureObjChunk::create();
    texLeft->setImage(imgLeft);

    OSG::ImageUnrecPtr imgRight = OSG::ImageFileHandler::the()->read(rightPath.c_str());
    OSG::TextureObjChunkUnrecPtr texRight = OSG::TextureObjChunk::create();
    texRight->setImage(imgRight);

    OSG::ImageUnrecPtr imgTop = OSG::ImageFileHandler::the()->read(topPath.c_str());
    OSG::TextureObjChunkUnrecPtr texTop = OSG::TextureObjChunk::create();
    texTop->setImage(imgTop);

    OSG::ImageUnrecPtr imgBottom = OSG::ImageFileHandler::the()->read(bottomPath.c_str());
    OSG::TextureObjChunkUnrecPtr texBottom = OSG::TextureObjChunk::create();
    texBottom->setImage(imgBottom);

    OSG::SkyBackgroundUnrecPtr skyBG = OSG::SkyBackground::create();
    skyBG->setFrontTexture(texFront);
    skyBG->setBackTexture(texBack);
    skyBG->setLeftTexture(texLeft);
    skyBG->setRightTexture(texRight);
    skyBG->setTopTexture(texTop);
    skyBG->setBottomTexture(texBottom);

    return skyBG;
}
