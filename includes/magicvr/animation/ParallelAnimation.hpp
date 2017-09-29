#ifndef MAGICVR_ANIMATIONS_HPP
#define MAGICVR_ANIMATIONS_HPP

#include <vector>
#include <memory>
#include "Animation.hpp"
#include <OpenSG/OSGTime.h>

class ParallelAnimation : public Animation {
    std::vector<std::shared_ptr<Animation>> _animations;
    const bool _stopIfNoAnimations;

    void removeStoppedAnimations();

public:
    static const bool STOP_IF_NO_ANIMATIONS = true;
    static const bool DO_NOT_STOP_IF_NO_ANIMATIONS = false;
    static const bool STOP_IF_NO_ANIMATIONS_DEFAULT = STOP_IF_NO_ANIMATIONS;

    ParallelAnimation();

    ParallelAnimation(bool stopIfNoAnimations);

    ParallelAnimation(bool stopIfNoAnimations,
                      std::initializer_list<std::shared_ptr<Animation>> animations);

    ParallelAnimation(
            std::initializer_list<std::shared_ptr<Animation>> animations);

    void add(std::shared_ptr<Animation> animation);

    void animate(OSG::Time dTime) override;

};


#endif //MAGICVR_ANIMATIONS_HPP
