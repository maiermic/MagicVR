#include <algorithm>
#include "magicvr/animation/ParallelAnimation.hpp"

ParallelAnimation::ParallelAnimation(bool stopIfNoAnimations,
                                     std::initializer_list<std::shared_ptr<Animation>> animations)
        : _stopIfNoAnimations(stopIfNoAnimations), _animations(animations) {
}

ParallelAnimation::ParallelAnimation(
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : ParallelAnimation(STOP_IF_NO_ANIMATIONS_DEFAULT, animations) {
}

ParallelAnimation::ParallelAnimation(bool stopIfNoAnimations)
        : ParallelAnimation(stopIfNoAnimations, {}) {
}

ParallelAnimation::ParallelAnimation()
        : ParallelAnimation(STOP_IF_NO_ANIMATIONS_DEFAULT) {
}

void ParallelAnimation::add(std::shared_ptr<Animation> animation) {
    if (_stopIfNoAnimations && _animations.empty()) {
        std::cerr << "Can not add animation to stopped parallel animation\n";
    } else {
        _animations.push_back(animation);
    }
}

void ParallelAnimation::animate(OSG::Time dTime) {
    for (auto animation : _animations) {
        animation->animate(dTime);
    }
    removeStoppedAnimations();
    if (_stopIfNoAnimations && _animations.empty()) {
        stop();
    }
}

void ParallelAnimation::removeStoppedAnimations() {
    _animations.erase(
            remove_if(begin(_animations),
                      end(_animations),
                      [](std::shared_ptr<Animation> animation) {
                          return animation->isStopped();
                      }),
            end(_animations));
}
