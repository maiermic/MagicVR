#include "magicvr/AppController.hpp"

void AppController::display(OSG::Time dTime) {
    _scene.update(dTime);
}

void AppController::keyboardDown(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            _scene.animateFireBubbles();
            break;
        case '2':
            _scene.animateWaterBubbles();
            break;
        case '3':
            _scene.animateThunderBubbles();
            break;
        case '4':
            _scene.animateWindBubbles();
            break;
        case '5':
            _scene.animateFire();
            break;
        case '6':
            _scene.fire().intensity(_scene.fire().intensity() + 0.1f);
            break;
        case '7':
            _scene.stopAnimateFireBubbles();
            break;
        case '8':
            _scene.stopAnimateWaterBubbles();
            break;
        case '9':
            _scene.stopAnimateThunderBubbles();
            break;
        case '0':
            _scene.stopAnimateWindBubbles();
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
    using Trajectory = std::vector<OSG::Vec3f>;
    _tricks.input_matches_pattern_lightning_stream.subscribe([&](double distance) {
        this->scene().animateThunderBubbles();
    });
    _tricks.input_matches_pattern_fire_stream.subscribe([&](double distance) {
        this->scene().animateFireBubbles();
    });
    _tricks.input_matches_pattern_water_stream.subscribe([&](double distance) {
        this->scene().animateWaterBubbles();
    });
    _tricks.input_matches_pattern_wind_stream.subscribe([&](double distance) {
        this->scene().animateWindBubbles();
    });
    _tricks.input_matches_pattern_quaterCircleFromAbove_stream.subscribe([&](double distance) {
        this->scene().animateWindBubbles();
    });
    _tricks.preprocessed_pattern_lightning_trajectory_stream.subscribe([&](Trajectory trajectory) {
        this->scene().showPatternTrajectory(std::move(trajectory));
    });
//    _tricks.preprocessed_input_trajectory_stream.subscribe([&](Trajectory trajectory) {
//        this->scene().showInputTrajectory(std::move(trajectory));
//    });
    _tricks.preprocessedWithoutRotation_input_trajectory_stream.subscribe([&](Trajectory trajectory) {
        this->scene().showPreprocessedInputTrajectory(std::move(trajectory));
    });
}

BezierCurve<> AppController::getShootingCurve(input::Tracker wand, OSG::Vec3f destination) const {
    using namespace magicvr::animation;

    OSG::Vec3f wandDirection;
    wand.orientation.multVec(OSG::Vec3f(0, 0, -1), wandDirection);
    wandDirection.normalize();

    auto worldWandPosition = wand.position / 100;
    return BezierCurve<> {
            worldWandPosition,
            worldWandPosition + wandDirection,
            destination,
            destination
    };
}