#include "magicvr/AppControllerWithWandSupport.hpp"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>
#include <input/Tracker.hpp>

namespace magicvr {
    AppControllerWithWandSupport::AppControllerWithWandSupport(
            input::RemoteManager &wand)
            : _wand(wand),
              _bulbCount(0) {
        showBulb(node::NO_BULB);
        root()->addChild(_wandNode.node().node());
        root()->addChild(_trajectoryNode.node());
        _tricks.input_matches_pattern_lightning_stream.subscribe(
                [&](double distance) {
                    showBulb(node::THUNDER_BULB);
                });
        _tricks.input_matches_pattern_water_stream.subscribe(
                [&](double distance) {
                    showBulb(node::WATER_BULB);
                });
        _tricks.input_matches_pattern_fire_stream.subscribe(
                [&](double distance) {
                    showBulb(node::FIRE_BULB);
                });
        _tricks.input_matches_pattern_circle_stream.subscribe(
                [&](double distance) {
                    _bulbCount++;
                    showBulb(node::DEFAULT_BULB);
                });
        _tricks.input_matches_pattern_quaterCircleFromAbove_stream.subscribe(
                [&](double distance) {
                    shootBulb();
                });
    }

    void AppControllerWithWandSupport::shootBulb() {
        if (_bulbCount == 0) {
            return;
        }
        std::cout << "bulb count: " << _bulbCount
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
        _bulbCount = std::max(0, _bulbCount - 1);
        std::cout << "bulb count after shoot: " << _bulbCount << '\n';
        if (_bulbCount == 0) {
            showBulb(node::NO_BULB);
        }
    }

    void AppControllerWithWandSupport::showBulb(magicvr::node::WandBulb bulb) {
        std::cout << "show bulb " << bulb << '\n';
        if (bulb == node::NO_BULB || _bulbCount >= 1) {
            _selectedWandBulb = bulb;
            _wandNode.showBulb(bulb);
        }
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

    void AppControllerWithWandSupport::shootFire() {
        AppController::shootFire(_wand.wand, OSG::Vec3f(-1.6f, 0, 0.2));
    }

}