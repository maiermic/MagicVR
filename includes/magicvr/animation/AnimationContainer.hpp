#ifndef MAGICVR_ANIMATIONCONTAINER_HPP
#define MAGICVR_ANIMATIONCONTAINER_HPP


#include "Animation.hpp"

class AnimationContainer : public Animation {
    Animation & _animation;
public:
    AnimationContainer(Animation &_animation);

    void animate(OSG::Time dTime) override;
};


#endif //MAGICVR_ANIMATIONCONTAINER_HPP
