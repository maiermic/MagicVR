#pragma once

#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <magicvr/animation/ParallelAnimation.hpp>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <input/Tracker.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/animation/BubbleAnimationsNode.hpp>

#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <magicvr/animation/BezierAnimation.hpp>
#include <magicvr/animation/EaseInOutAnimation.hpp>
#include <magicvr/Spiral.hpp>
#include <range/v3/to_container.hpp>
#include <magicvr/ranges/view/Circle.hpp>
#include <magicvr/ranges/view/rotate.hpp>
#include <magicvr/animation/ScaleAnimation.hpp>
#include <magicvr/animation/SequentialAnimation.hpp>
#include "PathSettings.hpp"
#include <magicvr/animation/BezierTranslationAnimation.hpp>
#include <input/Tracker.hpp>
#include <OpenSG/OSGSimpleGeometry.h>
#include <magicvr/animation/AnimationContainer.hpp>


#include <vector>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/Animation.hpp>
#include <magicvr/animation/ParallelAnimation.hpp>

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

    class BubbleAnimationsNode {
    public:
        BubbleAnimationsNode(Path modelPath,
                             const std::vector<BubbleData> &bubbleDatas);

        const OSG::NodeRecPtr node() const;

        Animation &animation();

    private:
        ParallelAnimation _animations;
        ComponentTransformNode _root;
        std::vector<details::InternalBubbleData> _bubbleDatas;

        void addBubblesToRoot();

        void addAnimations();
    };

}}
