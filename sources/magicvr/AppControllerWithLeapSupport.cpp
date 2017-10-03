#include "magicvr/AppControllerWithLeapSupport.hpp"
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>

namespace magicvr {

    void AppControllerWithLeapSupport::display(OSG::Time dTime) {
        _indexFingerTipPosition.update();
        if (_indexFingerTipPosition.hasChanged()) {
            const auto position =
                    _vectorConverter.toVec3f(
                            _indexFingerTipPosition.position());
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
        root()->addChild(createIndexFingerTipNode());
        root()->addChild(_trajectoryNode.node());
        _tricks.input_matches_pattern_L_stream.subscribe([&](double distance) {
            this->scene().animateThunderBubbles();
        });
        _tricks.input_matches_pattern_M_stream.subscribe([&](double distance) {
            this->scene().animateWaterBubbles();
        });
        _tricks.input_matches_pattern_water_stream.subscribe([&](double distance) {
            this->scene().animateWaterBubbles();
        });
    }

    NodeTransitPtr AppControllerWithLeapSupport::createIndexFingerTipNode() {
        GeometryRecPtr geo = makeSphereGeo(2, 1);
        SimpleMaterialRecPtr material = SimpleMaterialBase::create();
        material->setDiffuse(Color3f(1, 0.8f, 0));
        material->setAmbient(Color3f(0.8f, 0.2f, 0.2f));
        geo->setMaterial(material);
        return _indexFingerTipNode.node(makeNodeFor(geo));;
    }

    void AppControllerWithLeapSupport::keyboardDown(unsigned char key, int x,
                                                    int y) {
        AppController::keyboardDown(key, x, y);
        switch (key) {
            case ' ':
                _isRecordingTrajectory = true;
                break;
        }
    }

    void
    AppControllerWithLeapSupport::keyboardUp(unsigned char key, int x, int y) {
        AppController::keyboardUp(key, x, y);
        switch (key) {
            case ' ':
                _isRecordingTrajectory = false;
                _tricks.emit(std::move(_trajectoryNode.trajectory()));
                break;
        }
    }
}