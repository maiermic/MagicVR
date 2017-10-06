#pragma once

#include <OpenSG/OSGTime.h>
#include "SharedRefAnimationContainer.hpp"

namespace magicvr { namespace animation {

    class MaxTimeAnimation : public SharedRefAnimationContainer {
        OSG::Time _duration;
        OSG::Time _animationTime;
    public:
        MaxTimeAnimation(OSG::Time duration, std::shared_ptr<Animation> animation);

        void animate(OSG::Time dTime) override;
    };

}}

