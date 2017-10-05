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
