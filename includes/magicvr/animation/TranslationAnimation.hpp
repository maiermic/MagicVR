#ifndef MAGICVR_TRANSLATIONANIMATION_HPP
#define MAGICVR_TRANSLATIONANIMATION_HPP


#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGRefCountPtr.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTime.h>
#include "Animation.hpp"
#include "FracTimeAnimation.hpp"

class TranslationAnimation : public FracTimeAnimation {
    const OSG::ComponentTransformRecPtr _trans;
    const OSG::Vec3f _destination;
    const OSG::Vec3f _start;
    const OSG::Vec3f _movement;

public:

    TranslationAnimation(const OSG::ComponentTransformRecPtr trans,
                         OSG::Vec3f destination,
                         OSG::Time duration, bool startOver);

    void animateFracTime(OSG::Time fracTime) override;
};


#endif //MAGICVR_TRANSLATIONANIMATION_HPP
