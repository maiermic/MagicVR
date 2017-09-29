#include "magicvr/animation/BezierAnimation.hpp"

BezierAnimation::BezierAnimation(OSG::Time duration,
                                 const BezierCurve<TimeVector> bezier,
                                 const std::shared_ptr<Animation> animation)
        : FracTimeAnimation(duration),
          _animation(animation),
          _bezier(bezier) {}

void BezierAnimation::animateFracTime(OSG::Time fracTime) {
    _animation->animate(_bezier.atPercentage(fracTime).y());
}
