#include "magicvr/animation/AnimationContainer.hpp"

AnimationContainer::AnimationContainer(Animation &_animation)
        : _animation(_animation) {}

void AnimationContainer::animate(OSG::Time dTime) {
    _animation.animate(dTime);
    if (_animation.isStopped()) {
        stop();
    }
}

void AnimationContainer::stop() {
    Animation::stop();
    _animation.stop();
}
