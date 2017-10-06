#pragma once

#include <OpenSG/OSGContainerForwards.h>
#include "Animation.hpp"

namespace magicvr { namespace animation {
    class AnimationNode {
    public:
        virtual OSG::NodeRecPtr node()=0;

        virtual const OSG::NodeRecPtr node() const=0;

        virtual Animation &animation()=0;
    };
}}