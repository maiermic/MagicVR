#include "magicvr/MagicVrDesktopGlutFramework.hpp"
#include <OpenSG/OSGGLUTWindow.h>
#include <OpenSG/OSGSkyBackground.h>
#include <OpenSG/OSGImageFileHandler.h>
#include <OpenSG/OSGTextureObjChunk.h>

using namespace glutFramework;

int MagicVrDesktopGlutFramework::createWindow() {
    auto winid = GlutFramework::createWindow();
    OSG::GLUTWindowRecPtr gwin = OSG::GLUTWindowBase::create();
    gwin->setGlutId(winid);
    gwin->init();
    mgr = OSG::SimpleSceneManager::create();
    mgr->setWindow(gwin);
    mgr->setRoot(root());
    mgr->showAll();
//    mgr->setHeadlight(false);
    loadBackground();
    return winid;
}

OSG::Node *MagicVrDesktopGlutFramework::root() {
    return scene.root();
}

void MagicVrDesktopGlutFramework::keyboardDown(unsigned char key, int x, int y) {
    GlutFramework::keyboardDown(key, x, y);
    mgr->key(key, x, y);
}

void MagicVrDesktopGlutFramework::mouseButtonPress(int button, int state, int x, int y) {
    GlutFramework::mouseButtonPress(button, state, x, y);
    // react to mouse button presses
    if (state) {
        mgr->mouseButtonRelease(button, x, y);
    } else {
        mgr->mouseButtonPress(button, x, y);
    }
    glutPostRedisplay();
}

void MagicVrDesktopGlutFramework::mouseMove(int x, int y) {
    GlutFramework::mouseMove(x, y);
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void MagicVrDesktopGlutFramework::display(float dTime) {
    GlutFramework::display(dTime);
    scene.update();
    commitChanges();
    mgr->redraw();
    OSG::Thread::getCurrentChangeList()->clear();
}

MagicVrDesktopGlutFramework::MagicVrDesktopGlutFramework(Scene &scene) : scene(scene) {
    title = "MagicVR";
}

void MagicVrDesktopGlutFramework::reshape(int width, int height) {
    GlutFramework::reshape(width, height);
    mgr->resize(width, height);
}

void MagicVrDesktopGlutFramework::loadBackground() {
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

    mgr->setBackground(skyBG);
}
