//
// Created by vr2017 on 01.10.17.
//

#include "magicvr/animation/BubbleAnimation.hpp"

BubbleAnimation::BubbleAnimation(bool stopIfNoAnimations,
                                     std::initializer_list<std::shared_ptr<Animation>> animations)
        : _stopIfNoAnimations(stopIfNoAnimations), _animations(animations) {
}

BubbleAnimation::BubbleAnimation(
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : BubbleAnimation(STOP_IF_NO_ANIMATIONS_DEFAULT, animations) {
}

BubbleAnimation::BubbleAnimation(bool stopIfNoAnimations)
        : BubbleAnimation(stopIfNoAnimations, {}) {
}

BubbleAnimation::BubbleAnimation()
        : BubbleAnimation(STOP_IF_NO_ANIMATIONS_DEFAULT) {
}

void BubbleAnimation::add(std::shared_ptr<Animation> animation) {
    if (_stopIfNoAnimations && _animations.empty()) {
        std::cerr << "Can not add animation to stopped parallel animation\n";
    } else {
        _animations.push_back(animation);
    }
}

void BubbleAnimation::animate(OSG::Time dTime) {
    for (auto animation : _animations) {
        animation->animate(dTime);
    }
    removeStoppedAnimations();
    if (_stopIfNoAnimations && _animations.empty()) {
        stop();
    }
}

void BubbleAnimation::removeStoppedAnimations() {
    _animations.erase(
            remove_if(begin(_animations),
                      end(_animations),
                      [](std::shared_ptr<Animation> animation) {
                          return animation->isStopped();
                      }),
            end(_animations));
}