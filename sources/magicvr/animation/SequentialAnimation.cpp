#include "magicvr/animation/SequentialAnimation.hpp"
#include <deque>

void SequentialAnimation::animate(OSG::Time dTime) {
    if (_stopIfNoAnimations && _animations.empty()) {
        stop();
    } else {
        _animations.front()->animate(dTime);
        if (_animations.front()->isStopped()) {
            _animations.pop();
            if (_stopIfNoAnimations && _animations.empty()) {
                stop();
            }
        }
    }
}

SequentialAnimation::SequentialAnimation(
        bool stopIfNoAnimations,
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : _stopIfNoAnimations(stopIfNoAnimations),
          _animations(std::deque<std::shared_ptr<Animation>>(animations)) {
}

SequentialAnimation::SequentialAnimation(
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : SequentialAnimation(STOP_IF_NO_ANIMATIONS_DEFAULT, animations) {
}

SequentialAnimation::SequentialAnimation(bool stopIfNoAnimations)
        : SequentialAnimation(stopIfNoAnimations, {}) {
}

SequentialAnimation::SequentialAnimation()
        : SequentialAnimation(STOP_IF_NO_ANIMATIONS_DEFAULT) {
}

void SequentialAnimation::add(std::shared_ptr<Animation> animation) {
    _animations.push(animation);
}
