#ifndef MAGICVR_MAGICVRDESKTOPGLUTFRAMEWORK_HPP
#define MAGICVR_MAGICVRDESKTOPGLUTFRAMEWORK_HPP

#include "glutFramework/GlutFramework.hpp"
#include <OpenSG/OSGSimpleSceneManager.h>
#include <Scene.hpp>
#include <OpenSG/OSGTime.h>

class MagicVrDesktopGlutFramework : public glutFramework::GlutFramework {
    OSG::SimpleSceneManagerRefPtr mgr; // gets created in createWindow
    Scene &scene;
public:
    MagicVrDesktopGlutFramework(Scene &scene);

    int createWindow() override;

    void keyboardDown(unsigned char key, int x, int y) override;

    OSG::Node *root();

    void mouseButtonPress(int button, int state, int x, int y) override;

    void mouseMove(int x, int y) override;

    void display(OSG::Time dTime) override;

    void reshape(int width, int height) override;

};


#endif //MAGICVR_MAGICVRDESKTOPGLUTFRAMEWORK_HPP
