#include <algorithm>
#include "magicvr/animation/Animations.hpp"

void Animations::add(std::shared_ptr<Animation> animation) {
    _animations.push_back(animation);
}

void Animations::animate(OSG::Time dTime) {
    for (auto animation : _animations) {
        animation->animate(dTime);
    }
    removeStoppedAnimations();
}

void Animations::removeStoppedAnimations() {
    _animations.erase(
            remove_if(begin(_animations),
                      end(_animations),
                      [](std::shared_ptr<Animation> animation) {
                          return animation->isStopped();
                      }),
            end(_animations));
}
