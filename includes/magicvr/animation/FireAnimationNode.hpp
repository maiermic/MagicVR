#pragma once

#include <vector>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/Animation.hpp>
#include <magicvr/animation/ParallelAnimation.hpp>
#include "BubbleAnimationsNode.hpp"

namespace magicvr { namespace animation {

    class FireAnimationNode {
        ParallelAnimation _animations;
        ComponentTransformNode _root;
        float _intensity;

        std::vector<BubbleAnimationsNode> _bubbleAnimationNodes;

        void addBubblesToRoot();

        void addAnimations();

    public:
        FireAnimationNode();

        ComponentTransformNode node();

        const ComponentTransformNode node() const;

        Animation &animation();

        float intensity() const;

        void intensity(float intensity);
    };

}}