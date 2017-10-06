#include "magicvr/animation/MaxTimeAnimation.hpp"

namespace magicvr { namespace animation {

    void MaxTimeAnimation::animate(OSG::Time dTime) {
        _animation->animate(dTime);
        _animationTime += dTime;
        if (_animationTime >= _duration) {
            stop();
        }
    }

    MaxTimeAnimation::MaxTimeAnimation(OSG::Time duration,
                                       std::shared_ptr<Animation> animation)
            : SharedRefAnimationContainer(animation), _animationTime(0),
              _duration(duration) {}

}}