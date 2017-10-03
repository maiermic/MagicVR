//
// Created by vr2017 on 01.10.17.
//

#ifndef MAGICVR_BUBBLEANIMATION_HPP
#define MAGICVR_BUBBLEANIMATION_HPP


#include <magicvr/animation/ParallelAnimation.hpp>

class BubbleAnimation : public Animation {
    std::vector<std::shared_ptr<Animation>> _animations;
    const bool _stopIfNoAnimations;

    void removeStoppedAnimations();

public:
    static const bool STOP_IF_NO_ANIMATIONS = true;
    static const bool DO_NOT_STOP_IF_NO_ANIMATIONS = false;
    static const bool STOP_IF_NO_ANIMATIONS_DEFAULT = STOP_IF_NO_ANIMATIONS;

    BubbleAnimation();

    BubbleAnimation(bool stopIfNoAnimations);

    BubbleAnimation(bool stopIfNoAnimations,
                      std::initializer_list<std::shared_ptr<Animation>> animations);

    BubbleAnimation(
            std::initializer_list<std::shared_ptr<Animation>> animations);

    void add(std::shared_ptr<Animation> animation);

    void animate(OSG::Time dTime) override;

};


#endif //MAGICVR_BUBBLEANIMATION_HPP
