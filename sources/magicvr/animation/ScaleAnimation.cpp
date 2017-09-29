//
// Created by vr2017 on 28.09.17.
//

#include <magicvr/animation/FracTimeAnimation.hpp>
#include "magicvr/animation/ScaleAnimation.hpp"

ScaleAnimation::ScaleAnimation(
        const OSG::ComponentTransformRecPtr trans,
        OSG::Vec3f destination,
        OSG::Time duration) : FracTimeAnimation(duration), _trans(trans),
                              _destination(destination),
                              _start(trans->getScale()),
                              _movement(_destination - _start) {}

void ScaleAnimation::animateFracTime(OSG::Time fracTime) {
    _trans->setScale(_start + _movement * fracTime);
}
