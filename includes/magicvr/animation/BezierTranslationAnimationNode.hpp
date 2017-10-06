#pragma once

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGRefCountPtr.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTime.h>
#include <magicvr/animation/FracTimeAnimation.hpp>
#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/ComponentTransformNode.hpp>
#include "BezierTranslationAnimation.hpp"
#include "AnimationNode.hpp"

namespace magicvr { namespace animation {

    class BezierTranslationAnimationNode
            : public BezierTranslationAnimation, public AnimationNode {
        ComponentTransformNode _ctNode;

    public:

        BezierTranslationAnimationNode(ComponentTransformNode ctNode,
                                   BezierCurve<> bezier,
                                   OSG::Time duration);

        OSG::NodeRecPtr node() override;

        const OSG::NodeRecPtr node() const override;

        Animation &animation() override;
    };

}}
