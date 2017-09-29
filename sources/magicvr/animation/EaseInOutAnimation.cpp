#include "magicvr/animation/EaseInOutAnimation.hpp"

EaseInOutAnimation::EaseInOutAnimation(OSG::Time duration,
                                       const std::shared_ptr<Animation> &animation)
        : BezierAnimation(duration,
                          {
                                  TimeVector(0, 0),
                                  TimeVector(0.4, 0),
                                  TimeVector(0.6, 1),
                                  TimeVector(1, 1)
                          },
                          animation) {}
