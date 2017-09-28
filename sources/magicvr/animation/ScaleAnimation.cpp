//
// Created by vr2017 on 28.09.17.
//

#include "magicvr/animation/ScaleAnimation.hpp"

ScaleAnimation::ScaleAnimation(
        const OSG::ComponentTransformRecPtr trans,
        OSG::Vec3f destination,
        float duration) : _trans(trans),
                          _destination(destination),
                          _start(trans->getScale()),
                          _movement(_destination - _start),
                          _duration(duration),
                          _animationTime(0) {
}

void ScaleAnimation::animate(OSG::Time dTime) {
    _animationTime += dTime;
    if (fracTime() >= 1) {
        _trans->setScale(_destination);
        stop();
    } else {
        _trans->setScale(_start + _movement * fracTime());
    }
}

float ScaleAnimation::fracTime() const {
    return _animationTime / _duration;
}