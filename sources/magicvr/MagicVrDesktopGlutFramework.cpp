#include "magicvr/MagicVrDesktopGlutFramework.hpp"
#include <OpenSG/OSGGLUTWindow.h>
#include <magicvr/background.hpp>

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
    mgr->setBackground(loadBackground());
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
