#include "magicvr/animation/TranslationAnimation.hpp"

TranslationAnimation::TranslationAnimation(
        const OSG::ComponentTransformRecPtr trans,
        OSG::Vec3f destination,
        OSG::Time duration) : FracTimeAnimation(duration),
                              _trans(trans),
                              _destination(destination),
                              _start(trans->getTranslation()),
                              _movement(_destination - _start) {
}

void TranslationAnimation::animateFracTime(OSG::Time fracTime) {
    _trans->setTranslation(_start + _movement * fracTime);
}