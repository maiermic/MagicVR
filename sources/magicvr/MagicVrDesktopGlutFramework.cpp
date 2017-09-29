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
    mgr->setHeadlight(true);
    mgr->setBackground(loadBackground(SKYBOX_RES_1024)); // 256 | 512 | 1024 | 2048
    return winid;
}

OSG::Node *MagicVrDesktopGlutFramework::root() {
    return app.root();
}

void MagicVrDesktopGlutFramework::keyboardDown(unsigned char key, int x, int y) {
    GlutFramework::keyboardDown(key, x, y);
    mgr->key(key, x, y);
    app.keyboardDown(key, x, y);
}

void MagicVrDesktopGlutFramework::mouseButtonPress(int button, int state, int x, int y) {
    // react to mouse button presses
    if (state) {
        mgr->mouseButtonRelease(button, x, y);
    } else {
        mgr->mouseButtonPress(button, x, y);
    }
    glutPostRedisplay();
}

void MagicVrDesktopGlutFramework::mouseMove(int x, int y) {
    mgr->mouseMove(x, y);
    glutPostRedisplay();
}

void MagicVrDesktopGlutFramework::display(OSG::Time dTime) {
    app.display(dTime);
    commitChanges();
    mgr->idle();
    mgr->redraw();
    // the changelist should be cleared - else things could be copied multiple times
    OSG::Thread::getCurrentChangeList()->clear();
}

MagicVrDesktopGlutFramework::MagicVrDesktopGlutFramework(AppController &app)
        : app(app) {
    title("MagicVR");
}

void MagicVrDesktopGlutFramework::reshape(int width, int height) {
    mgr->resize(width, height);
}
