#pragma once


#include "SharedRefAnimationContainer.hpp"

namespace magicvr { namespace animation {

    class OnStopRefAnimation : public SharedRefAnimationContainer {
        std::function<void()> _onStop0;
        std::function<void(std::shared_ptr<Animation>)> _onStop1;
        bool _notified;

    public:
        OnStopRefAnimation(std::shared_ptr<Animation> animation,
                        std::function<void()> onStop);

        OnStopRefAnimation(std::shared_ptr<Animation> animation,
                        std::function<void(std::shared_ptr<Animation>)> onStop);

        void animate(OSG::Time dTime) override;
    };

}}

