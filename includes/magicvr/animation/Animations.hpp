#ifndef MAGICVR_ANIMATIONS_HPP
#define MAGICVR_ANIMATIONS_HPP

#include <vector>
#include <memory>
#include "Animation.hpp"
#include <OpenSG/OSGTime.h>

class Animations {
    std::vector<std::shared_ptr<Animation>> _animations;

    void removeStoppedAnimations();

public:
    void add(std::shared_ptr<Animation> animation);

    void animate(OSG::Time dTime);

};


#endif //MAGICVR_ANIMATIONS_HPP
