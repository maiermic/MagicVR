#pragma once

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>

#include "AnimationNode.hpp"
#include "ParallelAnimation.hpp"

namespace magicvr { namespace animation {
    class AnimationChildNode : public Animation {
        OSG::NodeRecPtr _parent;
        std::shared_ptr<AnimationNode> _child;

    public:
        AnimationChildNode(OSG::NodeRecPtr parent,
                           std::shared_ptr<AnimationNode> child);

        void animate(OSG::Time dTime) override;

        void stop() override;
    };
}}