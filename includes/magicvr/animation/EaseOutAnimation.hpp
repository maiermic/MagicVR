#ifndef MAGICVR_EASEOUTANIMATION_HPP
#define MAGICVR_EASEOUTANIMATION_HPP


#include "BezierAnimation.hpp"

class EaseOutAnimation : public BezierAnimation {
public:
    EaseOutAnimation(OSG::Time duration,
                     const std::shared_ptr<Animation> &animation);
};

#endif //MAGICVR_EASEOUTANIMATION_HPP
