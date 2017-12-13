#include "magicvr/AppControllerWithLeapSupport.hpp"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>

namespace magicvr {

    void AppControllerWithLeapSupport::display(OSG::Time dTime) {
        _indexFingerTipPosition.update();
        if (_indexFingerTipPosition.hasChanged()) {
            const auto position =
                    _vectorConverter.toVec3f(
                            _indexFingerTipPosition.position() + Leap::Vector(0, 100, 0));
            _wandDummy.position = position;
            _wandNode.node().translate(position);
            _indexFingerTipNode.moveTo(position);
            if (_isRecordingTrajectory) {
                _trajectoryNode.add(position);
            } else {
                _trajectoryNode.clear();
            }
        }

        AppController::display(dTime);
    }

    AppControllerWithLeapSupport::AppControllerWithLeapSupport(
            const leap::FingerTipPosition &_indexFingerTipPosition)
            : _indexFingerTipPosition(_indexFingerTipPosition),
              _isRecordingTrajectory(false) {
        _wandDummy = {
                OSG::Vec3f(0, 0, 0),
                OSG::Quaternion(),
        };
        root()->addChild(createIndexFingerTipNode());
        root()->addChild(_trajectoryNode.node());
    }

    NodeTransitPtr AppControllerWithLeapSupport::createIndexFingerTipNode() {
        GeometryRecPtr geo = makeSphereGeo(2, 0.5);
        SimpleMaterialRecPtr material = SimpleMaterialBase::create();
        material->setDiffuse(Color3f(0, 0.8f, 1));
        material->setAmbient(Color3f(0.2f, 0.2f, 0.8f));
        geo->setMaterial(material);
        return _indexFingerTipNode.node(makeNodeFor(geo));;
    }

    void AppControllerWithLeapSupport::keyboardDown(unsigned char key, int x,
                                                    int y) {
        AppController::keyboardDown(key, x, y);
        input::Tracker wand {
                {150, 150, 0},
                OSG::Quaternion({0, 0, -1}, OSG::osgDegree2Rad(90))
        };
        Vec3f destination(0, 0, 0);
        switch (key) {
            case ' ':
                _isRecordingTrajectory = true;
                break;
            case 'l':
                AppController::shootLight(wand);
                break;
            case '~':
                AppController::shootWater(wand, destination);
                break;
        }
    }

    void
    AppControllerWithLeapSupport::keyboardUp(unsigned char key, int x, int y) {
        AppController::keyboardUp(key, x, y);
        switch (key) {
            case '1':
                bulbCount(16);
                showBulb(node::FIRE_BULB);
                break;
            case '2':
                shootBulb();
                break;
            case ' ':
                _isRecordingTrajectory = false;
                _tricks.emit(std::move(_trajectoryNode.trajectory()));
                break;
        }
    }

    void AppControllerWithLeapSupport::shootLight() {
        AppController::shootLight(_wandDummy);
    }

    void AppControllerWithLeapSupport::shootWater() {
        AppController::shootWater(_wandDummy, OSG::Vec3f(-1.6f, 0, 0.2));
    }

    void AppControllerWithLeapSupport::shootFire() {
        AppController::shootFire(_wandDummy, OSG::Vec3f(-1.6f, 0, 0.2));
    }
}