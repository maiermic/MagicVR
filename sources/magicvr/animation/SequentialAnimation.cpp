#include "magicvr/animation/SequentialAnimation.hpp"
#include <algorithm>

void SequentialAnimation::animate(OSG::Time dTime) {
    if (_animations.empty()) {
        stop();
    } else {
        _animations.back()->animate(dTime);
        if (_animations.back()->isStopped()) {
            _animations.pop_back();
            if (_animations.empty()) {
                stop();
            }
        }
    }
}

SequentialAnimation::SequentialAnimation(
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : _animations(animations) {
    // reverse order to get FIFO
    std::reverse(std::begin(_animations), std::end(_animations));
}
