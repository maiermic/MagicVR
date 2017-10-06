#pragma once

#include <vector>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/Animation.hpp>
#include <magicvr/animation/ParallelAnimation.hpp>
#include "AnimationNode.hpp"

namespace magicvr { namespace animation {
    using BubbleData = float;
    using Path = const OSG::Char8 *;

    namespace details {
        class InternalBubbleData {
        public:
            BubbleData data;
            OSG::ComponentTransformRecPtr transformation;
            OSG::NodeRecPtr node;

            InternalBubbleData(BubbleData data,
                               OSG::ComponentTransformRecPtr transformation,
                               OSG::NodeRecPtr node);
        };

        std::vector<details::InternalBubbleData>
        buildBubbleDatas(Path modelPath,
                         const std::vector<BubbleData> &bubbleDatas);

        const OSG::NodeTransitPtr
        buildBubble(OSG::ComponentTransformRecPtr transCT,
                    OSG::NodeRecPtr model, float size);
    }

    class BubblesAnimationNode : public AnimationNode {
    public:
        BubblesAnimationNode(Path modelPath,
                             const std::vector<BubbleData> &bubbleDatas);

        ComponentTransformNode transNode();

        const ComponentTransformNode transNode() const;

        OSG::NodeRecPtr node() override;

        const OSG::NodeRecPtr node() const override;

        Animation &animation() override;

    private:
        ParallelAnimation _animations;
        ComponentTransformNode _root;
        std::vector<details::InternalBubbleData> _bubbleDatas;

        void addBubblesToRoot();

        void addAnimations();
    };

}}
