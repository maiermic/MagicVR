#ifndef MYPROJECT_MAGICVRGLUTFRAMEWORK_HPP
#define MYPROJECT_MAGICVRGLUTFRAMEWORK_HPP

#include <OSGCSM/OSGCAVESceneManager.h>
#include <Scene.h>
#include "glutFramework/GlutFramework.h"
#include "input/RemoteManager.h"

class MagicVrGlutFramework : public glutFramework::GlutFramework {
    OSGCSM::CAVEConfig &cfg;

    OSGCSM::CAVESceneManager &mgr;

    input::RemoteManager &remoteManager;

    Scene &scene;

    // head light fix (1/3)
    DirectionalLightRecPtr mainLight;


public:
    MagicVrGlutFramework(OSGCSM::CAVEConfig &cfg, OSGCSM::CAVESceneManager &mgr,
                         input::RemoteManager &remoteManager, Scene &scene,
                         DirectionalLightRecPtr mainLight);

    void keyboardDown(unsigned char key, int x, int y) override;

    void run() override;

    void reshape(int width, int height) override;
};


#endif //MYPROJECT_MAGICVRGLUTFRAMEWORK_HPP
