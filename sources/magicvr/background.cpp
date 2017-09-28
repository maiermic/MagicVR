#include "magicvr/background.hpp"
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGTextureObjChunk.h>

OSG::SkyBackgroundUnrecPtr loadBackground(Resolutions skyboxResolution) {
    std::string resolution = std::to_string((int) skyboxResolution);
    std::cout << "skyboxResolution: " << skyboxResolution << std::endl;

    std::string filePathBase = "models/skybox/" + resolution + "/envMap_cube_" + resolution + "_";
    std::cout << "filePathBase:  " << filePathBase << std::endl;

    std::string frontPath = filePathBase + "Front.png";
    std::string backPath = filePathBase + "Back.png";
    std::string leftPath = filePathBase + "Left.png";
    std::string rightPath = filePathBase + "Right.png";
    std::string topPath = filePathBase + "Top.png";
    std::string bottomPath = filePathBase + "Bottom.png";

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
