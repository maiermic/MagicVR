#ifndef MAGICVR_EASEINOUTANIMATION_HPP
#define MAGICVR_EASEINOUTANIMATION_HPP


#include "BezierAnimation.hpp"

class EaseInOutAnimation : public BezierAnimation {
public:
    EaseInOutAnimation(OSG::Time duration,
                       const std::shared_ptr<Animation> &animation);
};


#endif //MAGICVR_EASEINOUTANIMATION_HPP
