#include "magicvr/background.hpp"
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGTextureObjChunk.h>
#include "PathSettings.hpp"

OSG::SkyBackgroundUnrecPtr loadBackground(Resolutions skyboxResolution) {
    auto res = (int) skyboxResolution;
    std::string resolution = std::to_string(res);

    std::cout << "skyboxResolution: " << res << std::endl;

    /**
     * Get the Skybox CubeMap image */
    std::string bgImageFilePath = Path_Skybox_Root + resolution + Path_Skybox_Prefix + resolution + Path_Skybox_Suffix;

    std::cout << "Skybox ImagePath: " << bgImageFilePath << std::endl;
    OSG::ImageUnrecPtr mainImage = OSG::ImageFileHandler::the()->read(bgImageFilePath.c_str());

    /**
     * Create empty images as destinations for subimage */
    OSG::ImageUnrecPtr imgFront = ImageBase::create();
    OSG::ImageUnrecPtr imgBack = ImageBase::create();
    OSG::ImageUnrecPtr imgLeft = ImageBase::create();
    OSG::ImageUnrecPtr imgRight = ImageBase::create();
    OSG::ImageUnrecPtr imgTop = ImageBase::create();
    OSG::ImageUnrecPtr imgBottom = ImageBase::create();

    /**
     * Easier to change Skybox Images by croping them out
     * at runtime directly from the CubeMap Image exported from Blender
     *
     * Blender exports the environment maps in the format:
     *
     * Left   | Back | Right
     * Bottom | Top  | Front
     *
     * While subImage reads - offX from left to right
     *                      - offY from bottom to top */
    mainImage->subImage(2 * res, 0  , 0, res, res, 1, imgFront);
    mainImage->subImage(res    , res, 0, res, res, 1, imgBack);
    mainImage->subImage(0      , res, 0, res, res, 1, imgLeft);
    mainImage->subImage(2 * res, res, 0, res, res, 1, imgRight);
    mainImage->subImage(    res, 0  , 0, res, res, 1, imgTop);
    mainImage->subImage(0      , 0  , 0, res, res, 1, imgBottom);

    /**
     * Create Textures and set image to cropped images */
    OSG::TextureObjChunkUnrecPtr texFront = OSG::TextureObjChunk::create();
    texFront->setImage(imgFront);

    OSG::TextureObjChunkUnrecPtr texBack = OSG::TextureObjChunk::create();
    texBack->setImage(imgBack);

    OSG::TextureObjChunkUnrecPtr texLeft = OSG::TextureObjChunk::create();
    texLeft->setImage(imgLeft);

    OSG::TextureObjChunkUnrecPtr texRight = OSG::TextureObjChunk::create();
    texRight->setImage(imgRight);

    OSG::TextureObjChunkUnrecPtr texTop = OSG::TextureObjChunk::create();
    texTop->setImage(imgTop);

    OSG::TextureObjChunkUnrecPtr texBottom = OSG::TextureObjChunk::create();
    texBottom->setImage(imgBottom);

    /**
     * Create Skybox and set textures */
    OSG::SkyBackgroundUnrecPtr skyBG = OSG::SkyBackground::create();
    skyBG->setFrontTexture(texFront);
    skyBG->setBackTexture(texBack);
    skyBG->setLeftTexture(texLeft);
    skyBG->setRightTexture(texRight);
    skyBG->setTopTexture(texTop);
    skyBG->setBottomTexture(texBottom);

    return skyBG;
}
