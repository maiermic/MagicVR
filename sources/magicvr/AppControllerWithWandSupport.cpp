#include "magicvr/AppControllerWithWandSupport.hpp"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>
#include <input/Tracker.hpp>

namespace magicvr {
    AppControllerWithWandSupport::AppControllerWithWandSupport(
            input::Tracker &wand)
            : _isRecordingTrajectory(false), _wand(wand) {
        root()->addChild(createMovableNode());
    }

    void AppControllerWithWandSupport::display(OSG::Time dTime) {
        static auto lastWandPosition = _wand.position;
        if (lastWandPosition != _wand.position) {
            lastWandPosition = _wand.position;
            _movableNode.moveTo(_wand.position);
            if (_isRecordingTrajectory) {
                _trajectoryNode.add(_wand.position);
            }
        }
        AppController::display(dTime);
    }

    NodeTransitPtr AppControllerWithWandSupport::createMovableNode() {
        GeometryRecPtr geo = makeSphereGeo(2, 1);
        SimpleMaterialRecPtr material = SimpleMaterialBase::create();
        material->setDiffuse(Color3f(1, 0.8f, 0));
        material->setAmbient(Color3f(0.8f, 0.2f, 0.2f));
        geo->setMaterial(material);
        return _movableNode.node(makeNodeFor(geo));;
    }

}