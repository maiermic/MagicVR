#include "magicvr/AppController.hpp"

void AppController::display(OSG::Time dTime) {
    _scene.update(dTime);
}

void AppController::keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            _scene.unlockFire();
            break;
        case '2':
            _scene.unlockWater();
            break;
        case '3':
            _scene.unlockThunder();
            break;
        case '4':
            _scene.unlockEarth();
            break;
    }
}

const NodeRecPtr &AppController::root() const {
    return _scene.root();
}
