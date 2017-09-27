#ifndef MAGICVR_TRANSLATIONANIMATION_HPP
#define MAGICVR_TRANSLATIONANIMATION_HPP


#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGRefCountPtr.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTime.h>
#include "Animation.hpp"

class TranslationAnimation : public Animation {
    const OSG::ComponentTransformRecPtr _trans;
    const OSG::Vec3f _destination;
    const OSG::Vec3f _start;
    const OSG::Vec3f _movement;
    float _duration;
    float _animationTime;

public:

    TranslationAnimation(const OSG::ComponentTransformRecPtr trans,
                         OSG::Vec3f destination,
                         float duration);

    void animate(OSG::Time dTime) override;

    float fracTime() const;
};


#endif //MAGICVR_TRANSLATIONANIMATION_HPP
