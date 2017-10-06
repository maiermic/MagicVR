#include <magicvr/animation/BezierTranslationAnimationNode.hpp>

namespace magicvr { namespace animation {

    BezierTranslationAnimationNode::BezierTranslationAnimationNode(
            ComponentTransformNode ctNode, BezierCurve<> bezier,
            OSG::Time duration)
            : BezierTranslationAnimation(ctNode.trans(), bezier, duration),
              _ctNode(ctNode) {}

    OSG::NodeRecPtr BezierTranslationAnimationNode::node() {
        return _ctNode.node();
    }

    const OSG::NodeRecPtr BezierTranslationAnimationNode::node() const {
        return _ctNode.node();
    }

    Animation &BezierTranslationAnimationNode::animation() {
        return *this;
    }

}}
