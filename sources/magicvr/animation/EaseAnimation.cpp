#include "magicvr/animation/EaseAnimation.hpp"

EaseAnimation::EaseAnimation(OSG::Time duration,
                             const std::shared_ptr<Animation> &animation)
        : BezierAnimation(duration,
                          {
                                  TimeVector(0, 0),
                                  TimeVector(0.25, 0.1),
                                  TimeVector(0.25, 1),
                                  TimeVector(1, 1)
                          },
                          animation) {}
