//
// Created by vr2017 on 28.09.17.
//

#ifndef MAGICVR_FRACTIMEANIMATION_HPP
#define MAGICVR_FRACTIMEANIMATION_HPP


#include "Animation.hpp"

class FracTimeAnimation : public Animation {
    OSG::Time _duration;
    OSG::Time _animationTime;

public:
    explicit FracTimeAnimation(OSG::Time duration);

    void animate(OSG::Time dTime) override;

protected:
    virtual void animateFracTime(OSG::Time fracTime) = 0;

    OSG::Time fracTime() const;
};


#endif //MAGICVR_FRACTIMEANIMATION_HPP
