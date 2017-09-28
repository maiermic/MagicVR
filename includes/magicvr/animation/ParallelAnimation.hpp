#ifndef MAGICVR_ANIMATIONS_HPP
#define MAGICVR_ANIMATIONS_HPP

#include <vector>
#include <memory>
#include "Animation.hpp"
#include <OpenSG/OSGTime.h>

class ParallelAnimation : public Animation {
    std::vector<std::shared_ptr<Animation>> _animations;

    void removeStoppedAnimations();

public:
    ParallelAnimation() = default;

    ParallelAnimation(
            std::initializer_list<std::shared_ptr<Animation>> animations);

    void add(std::shared_ptr<Animation> animation);

    void animate(OSG::Time dTime) override;

};


#endif //MAGICVR_ANIMATIONS_HPP
