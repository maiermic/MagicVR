#include "magicvr/animation/EaseInAnimation.hpp"

EaseInAnimation::EaseInAnimation(OSG::Time duration,
                                 const std::shared_ptr<Animation> &animation)
        : BezierAnimation(duration,
                          {
                                  TimeVector(0, 0),
                                  TimeVector(0.4, 0),
                                  TimeVector(1, 1),
                                  TimeVector(1, 1)
                          },
                          animation) {}
