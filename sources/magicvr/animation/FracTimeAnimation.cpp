//
// Created by vr2017 on 28.09.17.
//

#include "magicvr/animation/FracTimeAnimation.hpp"

void FracTimeAnimation::animate(OSG::Time dTime) {

    _animationTime += dTime;
    animateFracTime(fracTime());
    if (_animationTime >= _duration) {
        if(_startOver){
            _animationTime = 0;
        } else {
            stop();
        }
    }
}

OSG::Time FracTimeAnimation::fracTime() const {
    return std::max(0.0, std::min(1.0, _animationTime / _duration));
}

FracTimeAnimation::FracTimeAnimation(OSG::Time duration, bool startOver)
        : _animationTime(0), _duration(duration), _startOver(startOver) {}
