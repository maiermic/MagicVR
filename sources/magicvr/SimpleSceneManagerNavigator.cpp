#include "magicvr/SimpleSceneManagerNavigator.hpp"

namespace magicvr {
    SimpleSceneManagerNavigator::SimpleSceneManagerNavigator()
            : _mgr(nullptr),
              _isMovingBackwards(false),
              _isMovingForwards(false) {}

    void SimpleSceneManagerNavigator::keyboardDown(unsigned char key) {
        switch (key) {
            case 'w':
                _isMovingForwards = true;
                break;
            case 's':
                _isMovingBackwards = true;
                break;
        }
    }

    void SimpleSceneManagerNavigator::keyboardUp(unsigned char key) {
        switch (key) {
            case 'w':
                _isMovingForwards = false;
                break;
            case 's':
                _isMovingBackwards = false;
                break;
        }
    }

    void SimpleSceneManagerNavigator::update() {
        if (_mgr == nullptr) {
            std::cout << "WARNING: manager is null in SimpleSceneManagerNavigator\n";
            return;
        }
        if (_isMovingForwards) {
            _mgr->getNavigator()->keyPress(OSG::Navigator::FORWARDS, 0, 0);
        } else if (_isMovingBackwards) {
            _mgr->getNavigator()->keyPress(OSG::Navigator::BACKWARDS, 0, 0);
        }
    }

    void SimpleSceneManagerNavigator::simpleSceneManager(
            const OSG::SimpleSceneManagerRefPtr &mgr) {
        _mgr = mgr;
    }
}