#include "magicvr/animation/SequentialAnimation.hpp"
#include <deque>

void SequentialAnimation::animate(OSG::Time dTime) {
    if (_animations.empty()) {
        stop();
    } else {
        _animations.front()->animate(dTime);
        if (_animations.front()->isStopped()) {
            _animations.pop();
            if (_animations.empty()) {
                stop();
            }
        }
    }
}

SequentialAnimation::SequentialAnimation(
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : _animations(std::deque<std::shared_ptr<Animation>> (animations)) {
}
