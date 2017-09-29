#ifndef MAGICVR_EASINGANIMATION_HPP
#define MAGICVR_EASINGANIMATION_HPP


#include <OpenSG/OSGVector.h>
#include "BezierCurve.hpp"
#include "FracTimeAnimation.hpp"

class BezierAnimation : public FracTimeAnimation {
public:
    using TimeVector = OSG::Vector<OSG::Time, 2>;

    BezierAnimation(OSG::Time duration,
    const BezierCurve<TimeVector> bezier,
    const std::shared_ptr<Animation> animation);

    void animateFracTime(OSG::Time fracTime) override;

private:
    const BezierCurve<TimeVector> _bezier;
    const std::shared_ptr<Animation> _animation;
};


#endif //MAGICVR_EASINGANIMATION_HPP
