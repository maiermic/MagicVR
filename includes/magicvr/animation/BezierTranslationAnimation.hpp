//
// Created by vr2017 on 05.10.17.
//

#ifndef MAGICVR_BEZIERTRANSLATIONANIMATION_HPP
#define MAGICVR_BEZIERTRANSLATIONANIMATION_HPP

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGRefCountPtr.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGTime.h>
#include <magicvr/animation/FracTimeAnimation.hpp>
#include <magicvr/animation/BezierCurve.hpp>

namespace magicvr { namespace animation {

    class BezierTranslationAnimation : public FracTimeAnimation {

        const OSG::ComponentTransformRecPtr _trans;
        const BezierCurve<> _bezier;

    public:

        BezierTranslationAnimation(const OSG::ComponentTransformRecPtr trans,
                                   BezierCurve<> bezier,
                                   OSG::Time duration);

        void animateFracTime(OSG::Time fracTime) override;
    };

}}

#endif //MAGICVR_BEZIERTRANSLATIONANIMATION_HPP
