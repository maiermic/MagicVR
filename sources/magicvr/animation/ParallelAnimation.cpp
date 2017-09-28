#include <algorithm>
#include "magicvr/animation/ParallelAnimation.hpp"

ParallelAnimation::ParallelAnimation(
        std::initializer_list<std::shared_ptr<Animation>> animations)
        : _animations(animations) {
}

void ParallelAnimation::add(std::shared_ptr<Animation> animation) {
    _animations.push_back(animation);
}

void ParallelAnimation::animate(OSG::Time dTime) {
    for (auto animation : _animations) {
        animation->animate(dTime);
    }
    removeStoppedAnimations();
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
