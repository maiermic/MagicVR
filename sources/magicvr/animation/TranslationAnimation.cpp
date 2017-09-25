#include "magicvr/animation/TranslationAnimation.hpp"

TranslationAnimation::TranslationAnimation(
        const OSG::ComponentTransformRecPtr trans,
        OSG::Vec3f destination,
        float duration) : _trans(trans),
                          _destination(destination),
                          _start(trans->getTranslation()),
                          _movement(_destination - _start),
                          _duration(duration),
                          _animationTime(0) {
}

void TranslationAnimation::animate(float dTime) {
    _animationTime += dTime;
    if (_animationTime >= _duration) {
        _trans->setTranslation(_destination);
        stop();
    } else {
        _trans->setTranslation(_start + _movement * fracTime());
    }
}

float TranslationAnimation::fracTime() const {
    return _animationTime / _duration;
}
