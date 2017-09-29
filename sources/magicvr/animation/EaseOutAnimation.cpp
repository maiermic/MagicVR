#include "magicvr/animation/EaseOutAnimation.hpp"

EaseOutAnimation::EaseOutAnimation(OSG::Time duration,
                                   const std::shared_ptr<Animation> &animation)
        : BezierAnimation(duration,
                          {
                                  TimeVector(0, 0),
                                  TimeVector(0, 0),
                                  TimeVector(0.2, 1),
                                  TimeVector(1, 1)
                          },
                          animation) {}
