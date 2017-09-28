#ifndef MAGICVR_SEQUENTIALANIMATION_HPP
#define MAGICVR_SEQUENTIALANIMATION_HPP


#include <magicvr/animation/Animation.hpp>
#include <memory>
#include <queue>

class SequentialAnimation : public Animation {
    std::queue<std::shared_ptr<Animation>> _animations;
public:
    SequentialAnimation(
            std::initializer_list<std::shared_ptr<Animation>> animations);

    void animate(OSG::Time dTime) override;
};


#endif //MAGICVR_SEQUENTIALANIMATION_HPP
