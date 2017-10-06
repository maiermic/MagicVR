#include "magicvr/animation/OnStopAnimation.hpp"

namespace magicvr { namespace animation {

    OnStopAnimation::OnStopAnimation(Animation &animation,
                                     std::function<void()> onStop)
            : AnimationContainer(animation),
              _onStop0(onStop),
              _notified(false) {}

    OnStopAnimation::OnStopAnimation(Animation &animation,
                                     std::function<void(Animation&)> onStop)
            : AnimationContainer(animation),
              _onStop1(onStop),
              _notified(false) {}

    void OnStopAnimation::animate(OSG::Time dTime) {
        AnimationContainer::animate(dTime);
        if (isStopped() && !_notified) {
            if (_onStop0) {
                _onStop0();
            } else if (_onStop1) {
                _onStop1(_animation);
            } else {
                std::cout << "WARNING: OnStopAnimation has no callable event listener\n";
            }
            _notified = true;
        }
    }
}}