#include "magicvr/AppController.hpp"

namespace magicvr {

void AppController::display(OSG::Time dTime) {
    _timeSinceStart += dTime;
    if (_isShooting && _nextShotTime < _timeSinceStart) {
        shootBulb();
    }
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
    bulbCount(0);
    showBulb(node::NO_BULB);
    root()->addChild(_wandNode.node().node());
    root()->addChild(_trajectoryNode.node());
    _tricks.input_matches_pattern_lightning_stream.subscribe([&](double distance) {
        this->scene().animateThunderBubbles();
        std::cout << "lightning distance " << distance << '\n';
        showBulb(node::THUNDER_BULB);
    });
    _tricks.input_matches_pattern_fire_stream.subscribe([&](double distance) {
        this->scene().animateFireBubbles();
        std::cout << "fire distance " << distance << '\n';
        showBulb(node::FIRE_BULB);
    });
    _tricks.input_matches_pattern_water_stream.subscribe([&](double distance) {
        this->scene().animateWaterBubbles();
        std::cout << "water distance " << distance << '\n';
        showBulb(node::WATER_BULB);
    });
    _tricks.input_matches_pattern_wind_stream.subscribe([&](double distance) {
        this->scene().animateWindBubbles();
        std::cout << "wind distance " << distance << '\n';
    });
//    _tricks.preprocessed_pattern_circle_trajectory_stream.subscribe([&](Trajectory trajectory) {
//        this->scene().showPatternTrajectory(std::move(trajectory));
//    });
//    _tricks.preprocessed_pattern_lightning_trajectory_stream.subscribe([&](Trajectory trajectory) {
//        this->scene().showPatternTrajectory(std::move(trajectory));
//    });
//    _tricks.preprocessed_input_trajectory_stream.subscribe([&](Trajectory trajectory) {
//        this->scene().showInputTrajectory(std::move(trajectory));
//    });
//    _tricks.preprocessedWithoutRotation_input_trajectory_stream.subscribe([&](Trajectory trajectory) {
//        this->scene().showPreprocessedInputTrajectory(std::move(trajectory));
//    });
    _tricks.input_matches_pattern_circle_stream.subscribe(
            [&](double distance) {
                std::cout << "circle distance " << distance << '\n';
//                showDefaultBulb();
            });
    _tricks.input_matches_pattern_circle2_stream.subscribe(
            [&](double distance) {
                std::cout << "circle2 distance " << distance << '\n';
//                if (bulbCount() >= 1) {
//                    bulbCount(bulbCount() * 2);
//                }
            });
    _tricks.input_matches_pattern_quaterCircleFromAbove_stream.subscribe(
            [&](double distance) {
                std::cout << "quaterCircleFromAbove distance " << distance << '\n';
                if (!_isShooting) {
                    shootBulb();
                }
            });
    _tricks.circle_comparison_data_stream
            .subscribe([&](const circle_comparison_data &data) {
                const auto to_trajectory_3d = [](const model::trajectory_2d &trajectory) {
                    return trajectory |
                           ::ranges::view::transform([](OSG::Vec2f v) {
                               return OSG::Vec3f(v.x(), v.y(), 100);
                           }) |
                           ::ranges::to_vector;
                };
                this->scene().showPreprocessedInputTrajectory(
                        to_trajectory_3d(data.preprocessed_input_trajectory)
                );
                this->scene().showPatternTrajectory(
                        to_trajectory_3d(data.preprocessed_pattern_trajectory)
                );
                if (data.distance.real_distance < 15.0) {
                    if (data.circle_segment_info.winding_number == 1) {
                        showDefaultBulb();
                    } else if (data.circle_segment_info.winding_number > 1){
                        if (bulbCount() >= 1) {
                            bulbCount(bulbCount() * data.circle_segment_info.winding_number);
                        }
                    }
                }
            });
    _tricks.left_circle_comparison_data_stream
            .subscribe([&](const circle_comparison_data &data) {
                std::cout << "left preprocessed circle estimation:\n"
                          << "  winding_number: " << data.circle_segment_info.winding_number
                          << "  radius: " << data.circle_segment_info.radius
                          << "  distance: " << data.distance.real_distance
                          << '\n';
            });
    _tricks.right_circle_comparison_data_stream
            .subscribe([&](const circle_comparison_data &data) {
                std::cout << "right preprocessed circle estimation:\n"
                          << "  winding_number: " << data.circle_segment_info.winding_number
                          << "  radius: " << data.circle_segment_info.radius
                          << "  distance: " << data.distance.real_distance
                          << '\n';
            });
}

    void AppController::showDefaultBulb() {
        if (bulbCount() < 1) {
            bulbCount(1);
        }
        if (_selectedWandBulb == node::NO_BULB) {
            showBulb(node::DEFAULT_BULB);
        }
    }

    void AppController::shootBulb() {
        if (_bulbCount == 0) {
            return;
        }
        _isShooting = true;
        _nextShotTime = _timeSinceStart + getShootingTime();
        std::cout << "bulb count: " << bulbCount()
                  << ", selected: " << _selectedWandBulb
                  << '\n';
        switch (_selectedWandBulb) {
            case node::THUNDER_BULB:
                shootLight();
                break;
            case node::WATER_BULB:
                shootWater();
                break;
            case node::FIRE_BULB:
                shootFire();
                break;
            default:
                return;
        }
        bulbCount(bulbCount() - 1);
        std::cout << "bulb count after shoot: " << bulbCount() << '\n';
        if (bulbCount() == 0) {
            showBulb(node::NO_BULB);
        }
    }

    void AppController::showBulb(magicvr::node::WandBulb bulb) {
        std::cout << "show bulb " << bulb << '\n';
        if (bulb == node::NO_BULB || bulbCount() >= 1) {
            _selectedWandBulb = bulb;
            _wandNode.showBulb(bulb);
        }
    }

    int AppController::bulbCount() const {
        return _bulbCount;
    }

    void AppController::bulbCount(int count) {
        _bulbCount = std::max(0, count);
        _wandNode.node().scale(std::log2f(bulbCount() + 1));
        if (bulbCount() == 0) {
            _isShooting = false;
        }
    }

BezierCurve<> AppController::getShootingCurve(input::Tracker wand, OSG::Vec3f destination,
                                              float directionFactor) const {
    using namespace magicvr::animation;

    OSG::Vec3f wandDirection;
    wand.orientation.multVec(OSG::Vec3f(0, 0, -1), wandDirection);
    wandDirection.normalize();

    auto worldWandPosition = wand.position / 100;
    return BezierCurve<> {
            worldWandPosition,
            worldWandPosition + wandDirection * directionFactor,
            destination,
            destination
    };
}

void AppController::shootLight(input::Tracker wand) {
    auto lanternPosition = scene().getLanternPosition();
    lanternPosition[1] += 0.2;
    scene().shootLight(
            getShootingCurve(wand, lanternPosition, 10.0f),
            [](Scene::AnimationPtr animation) {
                std::cout << "shooted light reached destination\n";
            }
    );
}

void AppController::shootWater(input::Tracker wand, OSG::Vec3f destination) {
    scene().shootWater(
            getShootingCurve(wand, destination, 1.0f),
            [&](Scene::AnimationPtr animation) {
                scene().fire().intensity(scene().fire().intensity() - 0.1f);
            }
    );
}

void AppController::shootFire(input::Tracker wand, OSG::Vec3f destination) {
    scene().shootFire(
            getShootingCurve(wand, destination, 1.0f),
            [&](Scene::AnimationPtr animation) {
                scene().fire().intensity(scene().fire().intensity() + 0.1f);
            }
    );
}

} // namespace magicvr