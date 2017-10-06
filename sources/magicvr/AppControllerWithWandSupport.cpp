#include "magicvr/AppControllerWithWandSupport.hpp"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>
#include <input/Tracker.hpp>

namespace magicvr {
    AppControllerWithWandSupport::AppControllerWithWandSupport(
            input::RemoteManager &wand)
            : _wand(wand) {
        root()->addChild(createMovableNode());
        root()->addChild(_trajectoryNode.node());
    }

    void AppControllerWithWandSupport::display(OSG::Time dTime) {
        static auto lastWandPosition = _wand.wand.position;
        static bool _hasBeenRecordingTrajectory = false;
        const bool _isRecordingTrajectory = _wand.buttons[input::RemoteManager::BACK];
        if (lastWandPosition != _wand.wand.position) {
            lastWandPosition = _wand.wand.position;
            _movableNode.moveTo(_wand.wand.position);
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

    NodeTransitPtr AppControllerWithWandSupport::createMovableNode() {
        GeometryRecPtr geo = makeSphereGeo(2, 1);
        SimpleMaterialRecPtr material = SimpleMaterialBase::create();
        material->setDiffuse(Color3f(1, 0.8f, 0));
        material->setAmbient(Color3f(0.8f, 0.2f, 0.2f));
        geo->setMaterial(material);
        return _movableNode.node(makeNodeFor(geo));;
    }

    void AppControllerWithWandSupport::keyboardDown(unsigned char key, int x,
                                                    int y) {
        AppController::keyboardDown(key, x, y);
        switch (key){
            case 'l':
                scene().shootLight(_wand.wand,Vec3f(0,0,0));
                break;
            case '~':
                scene().shootWater(_wand.wand,Vec3f(0,0,0));
                break;
        }
    }

}