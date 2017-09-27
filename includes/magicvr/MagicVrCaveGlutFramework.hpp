#ifndef MYPROJECT_MAGICVRGLUTFRAMEWORK_HPP
#define MYPROJECT_MAGICVRGLUTFRAMEWORK_HPP

#include <OSGCSM/OSGCAVESceneManager.h>
#include <OpenSG/OSGTime.h>
#include <Scene.hpp>
#include "GlutFramework.hpp"
#include "input/RemoteManager.hpp"

class MagicVrCaveGlutFramework : public glutFramework::GlutFramework {
    OSGCSM::CAVEConfig &cfg;

    OSGCSM::CAVESceneManager &mgr;

    input::RemoteManager &remoteManager;

    Scene &scene;

    // head light fix (1/3)
    DirectionalLightRecPtr mainLight;

    int createWindow() override;

    void clearControlWindow() const;

public:
    MagicVrCaveGlutFramework(OSGCSM::CAVEConfig &cfg, OSGCSM::CAVESceneManager &mgr,
                         input::RemoteManager &remoteManager, Scene &scene,
                         DirectionalLightRecPtr mainLight);

    void keyboardDown(unsigned char key, int x, int y) override;

    void idle() override;

    void reshape(int width, int height) override;

    void display(OSG::Time dTime) override;
};


#endif //MYPROJECT_MAGICVRGLUTFRAMEWORK_HPP
