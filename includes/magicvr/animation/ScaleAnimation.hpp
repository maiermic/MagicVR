//
// Created by vr2017 on 28.09.17.
//

#ifndef MAGICVR_SCALEANIMATION_HPP
#define MAGICVR_SCALEANIMATION_HPP


#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGRefCountPtr.h>
#include <OpenSG/OSGComponentTransform.h>
#include "Animation.hpp"

class ScaleAnimation : public Animation {

    const OSG::ComponentTransformRecPtr _trans;
    const OSG::Vec3f _destination;
    const OSG::Vec3f _start;
    const OSG::Vec3f _movement;
    float _duration;
    float _animationTime;

public:

    ScaleAnimation(const OSG::ComponentTransformRecPtr trans,
                         OSG::Vec3f destination,
                         float duration);

    void animate(float dTime) override;

    float fracTime() const;
};


#endif //MAGICVR_SCALEANIMATION_HPP
