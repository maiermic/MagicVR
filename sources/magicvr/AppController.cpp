#include "magicvr/AppController.hpp"

void AppController::display(OSG::Time dTime) {
    _scene.update(dTime);
}

void AppController::keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
//        case '1':
//            _scene.unlockFire();
//            break;
//        case '2':
//            _scene.unlockWater();
//            break;
//        case '3':
//            _scene.unlockThunder();
//            break;
//        case '4':
//            _scene.unlockEarth();
//            break;
        case '5':
            _scene.animateFireBubbles();
            break;
        case '6':
            _scene.animateWaterBubbles();
            break;
        case '7':
            _scene.animateThunderBubbles();
            break;
        case '8':
            _scene.animateWindBubbles();
            break;
    }
}

const NodeRecPtr &AppController::root() const {
    return _scene.root();
}
