#ifndef MAGICVR_EASEANIMATION_HPP
#define MAGICVR_EASEANIMATION_HPP


#include "BezierAnimation.hpp"

class EaseAnimation : public BezierAnimation {
public:
    EaseAnimation(OSG::Time duration,
                  const std::shared_ptr<Animation> &animation);
};


#endif //MAGICVR_EASEANIMATION_HPP
