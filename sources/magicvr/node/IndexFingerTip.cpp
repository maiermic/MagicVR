#include "magicvr/node/IndexFingerTip.hpp"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGSimpleGeometry.h>

namespace magicvr { namespace node {
    using namespace OSG;

    Vec3f toVec3f(const Leap::Vector &lv) {
        return Vec3f(lv.x, lv.y, lv.z);
    }

    IndexFingerTip::IndexFingerTip(Leap::Controller &controller)
            : _controller(controller) {}

    NodeTransitPtr IndexFingerTip::node() {
        if (_node == nullptr) {
            _transformer = ComponentTransformBase::create();
            _node = makeNodeFor(_transformer);
            _node->addChild(makeBox(10, 10, 10, true, true, true));
        }
        return NodeTransitPtr(_node);
    }

    void IndexFingerTip::update() {
        auto frame = _controller.frame();
        for (auto &&finger : frame.fingers()) {
            if (Leap::Finger::TYPE_INDEX == finger.type()) {
                onIndexFinger(finger);
            }
        }
    }

    void IndexFingerTip::onIndexFinger(const Leap::Finger &finger) {
        static const auto movementPercision = 5.0f;
        static const Vec3f leapZeroPoint(0, -100, 0);
        if (_node != nullptr) {
            const auto position =
                    (toVec3f(finger.tipPosition()) + leapZeroPoint) /
                    movementPercision;
            _transformer->setTranslation(position);
        }
    }

}}