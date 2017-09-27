#include "magicvr/MagicVrCaveGlutFramework.hpp"

void MagicVrCaveGlutFramework::keyboardDown(unsigned char key, int x, int y) {
    glutFramework::GlutFramework::keyboardDown(key, x, y);
    Real32 ed;
    switch (key) {
        case 'q':
        case 27:
            exit(EXIT_SUCCESS);
            break;
        case 'e':
            ed = mgr.getEyeSeparation() * .9f;
            std::cout << "Eye distance: " << ed << '\n';
            mgr.setEyeSeparation(ed);
            break;
        case 'E':
            ed = mgr.getEyeSeparation() * 1.1f;
            std::cout << "Eye distance: " << ed << '\n';
            mgr.setEyeSeparation(ed);
            break;
        case 'h':
            cfg.setFollowHead(!cfg.getFollowHead());
            std::cout << "following head: " << std::boolalpha << cfg.getFollowHead() << '\n';
            break;
        case 'i':
            remoteManager.print_tracker();
            break;
        default:
            std::cout << "Key '" << key << "' ignored\n";
    }
}

MagicVrCaveGlutFramework::MagicVrCaveGlutFramework(OSGCSM::CAVEConfig &cfg, OSGCSM::CAVESceneManager &mgr,
                                           input::RemoteManager &remoteManager, Scene &scene,
                                           DirectionalLightRecPtr mainLight)
        : cfg(cfg), mgr(mgr), remoteManager(remoteManager),
          scene(scene), mainLight(mainLight) {
    title = "MagicVR Control Window";
}

void MagicVrCaveGlutFramework::reshape(int width, int height) {
    glutFramework::GlutFramework::reshape(width, height);
    mgr.resize(width, height);
}

void MagicVrCaveGlutFramework::run() {
    glutFramework::GlutFramework::run();
    remoteManager.check_tracker();

    scene.update();

    const auto speed = 1.f;
    auto head = remoteManager.head;
    mgr.setUserTransform(head.position, head.orientation);
    mgr.setTranslation(mgr.getTranslation() + speed * remoteManager.analog_values);

    // head light fix (2/3)
    Matrix4f mat;
    mat.setRotate(head.orientation);
    auto dir = mat * Vec3f(0.f, 0.f, 1.f);
    mainLight->setDirection(dir);

    commitChanges();
    mgr.redraw();
    // the changelist should be cleared - else things could be copied multiple times
    OSG::Thread::getCurrentChangeList()->clear();
}
