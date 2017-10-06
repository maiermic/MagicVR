#pragma once


#include "Animation.hpp"

namespace magicvr { namespace animation {

    class SharedRefAnimationContainer : public Animation {
    protected:
        std::shared_ptr<Animation> _animation;
    public:
        SharedRefAnimationContainer(std::shared_ptr<Animation> _animation);

        virtual void animate(OSG::Time dTime) override;

        void stop() override;
    };

}}
