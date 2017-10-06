#pragma once


#include "AnimationContainer.hpp"

namespace magicvr { namespace animation {

    class OnStopAnimation : public AnimationContainer {
        std::function<void()> _onStop0;
        std::function<void(Animation&)> _onStop1;
        bool _notified;

    public:
        OnStopAnimation(Animation &animation,
                        std::function<void()> onStop);

        OnStopAnimation(Animation &animation,
                        std::function<void(Animation&)> onStop);

        void animate(OSG::Time dTime) override;
    };

}}

