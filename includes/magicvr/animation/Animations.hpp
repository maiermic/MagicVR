#ifndef MAGICVR_ANIMATIONS_HPP
#define MAGICVR_ANIMATIONS_HPP

#include <vector>
#include <memory>
#include "Animation.hpp"
#include <OpenSG/OSGTime.h>

class Animations : public Animation {
    std::vector<std::shared_ptr<Animation>> _animations;

    void removeStoppedAnimations();

public:
    void add(std::shared_ptr<Animation> animation);

    void animate(OSG::Time dTime) override;

};


#endif //MAGICVR_ANIMATIONS_HPP
