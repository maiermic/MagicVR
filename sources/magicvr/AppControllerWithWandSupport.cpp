#include "magicvr/AppControllerWithWandSupport.hpp"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>
#include <input/Tracker.hpp>

namespace magicvr {
    AppControllerWithWandSupport::AppControllerWithWandSupport(
            input::RemoteManager &wand)
            : _wand(wand) {
        root()->addChild(_wandNode.node().node());
        root()->addChild(_trajectoryNode.node());
        _tricks.input_matches_pattern_lightning_stream.subscribe(
                [&](double distance) {
                    shootLight();
                    _wandNode.showBulb(node::THUNDER_BULB);
                });
        _tricks.input_matches_pattern_water_stream.subscribe(
                [&](double distance) {
                    shootWater();
                    _wandNode.showBulb(node::WATER_BULB);
                });
    }

    void AppControllerWithWandSupport::display(OSG::Time dTime) {
        static auto lastWandPosition = _wand.wand.position;
        static bool _hasBeenRecordingTrajectory = false;
        const bool _isRecordingTrajectory = _wand.buttons[input::RemoteManager::BACK];
        if (lastWandPosition != _wand.wand.position) {
            lastWandPosition = _wand.wand.position;
            _wandNode.node().translate(_wand.wand.position);
            if (_isRecordingTrajectory) {
                _trajectoryNode.add(_wand.wand.position);
            } else if (_hasBeenRecordingTrajectory) {
                _tricks.emit(std::move(_trajectoryNode.trajectory()));
                _trajectoryNode.clear();
            }
        }
        AppController::display(dTime);
        _hasBeenRecordingTrajectory = _isRecordingTrajectory;
    }

    void AppControllerWithWandSupport::keyboardDown(unsigned char key, int x,
                                                    int y) {
        AppController::keyboardDown(key, x, y);
        switch (key) {
            case 'l':
                shootLight();
                break;
            case '~':
                shootWater();
                break;
        }
    }

    void AppControllerWithWandSupport::shootLight() {
        AppController::shootLight(_wand.wand);
    }

    void AppControllerWithWandSupport::shootWater() {
        AppController::shootWater(_wand.wand, OSG::Vec3f(-1.6f, 0, 0.2));
    }

}