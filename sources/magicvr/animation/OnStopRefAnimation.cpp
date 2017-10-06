#include "magicvr/animation/OnStopRefAnimation.hpp"

namespace magicvr { namespace animation {

    OnStopRefAnimation::OnStopRefAnimation(
            std::shared_ptr<Animation> animation,
            std::function<void()> onStop
    ) : SharedRefAnimationContainer(animation),
        _onStop0(onStop),
        _notified(false) {}

    OnStopRefAnimation::OnStopRefAnimation(
            std::shared_ptr<Animation> animation,
            std::function<void(std::shared_ptr<Animation>)> onStop
    ) : SharedRefAnimationContainer(animation),
        _onStop1(onStop),
        _notified(false) {}

    void OnStopRefAnimation::animate(OSG::Time dTime) {
        SharedRefAnimationContainer::animate(dTime);
        if (isStopped() && !_notified) {
            if (_onStop0) {
                _onStop0();
            } else if (_onStop1) {
                _onStop1(_animation);
            } else {
                std::cout
                        << "WARNING: OnStopRefAnimation has no callable event listener\n";
            }
            _notified = true;
        }
    }
}}