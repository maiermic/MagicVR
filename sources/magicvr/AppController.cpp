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

void AppController::keyboardUp(unsigned char key, int x, int y) {
}

Scene &AppController::scene() {
    return _scene;
}

AppController::AppController() {
    _tricks.input_matches_pattern_L_stream.subscribe([&](double distance) {
        this->scene().animateThunderBubbles();
    });
    _tricks.input_matches_pattern_M_stream.subscribe([&](double distance) {
        this->scene().animateWaterBubbles();
    });
    _tricks.input_matches_pattern_water_stream.subscribe([&](double distance) {
        this->scene().animateWaterBubbles();
    });
    _tricks.input_matches_pattern_wind_stream.subscribe([&](double distance) {
        this->scene().animateWindBubbles();
    });
}
