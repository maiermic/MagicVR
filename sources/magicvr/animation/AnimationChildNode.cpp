#include "magicvr/animation/AnimationChildNode.hpp"

namespace magicvr { namespace animation {

    AnimationChildNode::AnimationChildNode(OSG::NodeRecPtr parent,
                                           std::shared_ptr<AnimationNode> child)
            : _parent(parent), _child(child) {
        _parent->addChild(_child->node());
    }

    void AnimationChildNode::animate(OSG::Time dTime) {
        _child->animation().animate(dTime);
        if (_child->animation().isStopped()) {
            stop();
        }
    }

    void AnimationChildNode::stop() {
        Animation::stop();
        _parent->subChild(_child->node());
    }
}}