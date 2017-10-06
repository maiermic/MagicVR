#include "magicvr/animation/FireAnimationNode.hpp"

#include <algorithm>
#include <range/v3/utility/functional.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/for_each.hpp>
#include <range/v3/all.hpp>
#include <range/v3/to_container.hpp>
#include <OpenSG/OSGSceneFileHandler.h>
#include <magicvr/animation/Animation.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include <magicvr/animation/ScaleAnimation.hpp>
#include <PathSettings.hpp>
#include <magicvr/animation/AnimationContainer.hpp>
#include <magicvr/ranges/view/range.hpp>
#include <magicvr/ranges/view/Circle.hpp>
#include "magicvr/animation/BubbleAnimationsNode.hpp"
#include "magicvr/util/clamp.hpp"

namespace magicvr { namespace animation {

    FireAnimationNode::FireAnimationNode()
            : _animations(false) {
        intensity(0);
        using magicvr::ranges::view::rangeV;
        magicvr::ranges::view::Circle c(0.1);
        float y = 0.1f;
        for (Vec2f v : c.sample(0, 360, 60) | ::ranges::to_vector) {
            BubbleAnimationsNode ban(
                    Path_Model_FireBubble,
                    rangeV(0.3f, 1.0f, 0.1f)
            );
            ban.transNode().translate(v.x(), y, v.y()).scale(3, 1, 3);
            _bubbleAnimationNodes.push_back(ban);
            y = -y;
        }

        BubbleAnimationsNode middleLower(Path_Model_FireBubble, rangeV(0.3f, 1.0f, 0.1f));
        BubbleAnimationsNode middleUpper(Path_Model_FireBubble, rangeV(0.3f, 1.0f, 0.1f));
        BubbleAnimationsNode left(Path_Model_ThunderBubble, rangeV(0.3f, 1.0f, 0.1f));
        BubbleAnimationsNode right(Path_Model_ThunderBubble, rangeV(0.3f, 1.0f, 0.1f));
        middleLower.transNode().translate(0, 0.1, 0).scale(3, 1, 3);
        left.transNode().translate(0.05f, 0, 0).scale(3, 1, 3);
        right.transNode().translate(-0.05f, 0, 0).scale(3, 1, 3);
        middleUpper.transNode().translate(0, -0.1f, 0).scale(3, 1, 3);
        _bubbleAnimationNodes.push_back(middleLower);
        _bubbleAnimationNodes.push_back(left);
        _bubbleAnimationNodes.push_back(right);
        _bubbleAnimationNodes.push_back(middleUpper);

        addBubblesToRoot();
        addAnimations();
    }

    ComponentTransformNode FireAnimationNode::node() {
        return _root;
    }

    const ComponentTransformNode FireAnimationNode::node() const {
        return _root;
    }

    Animation &FireAnimationNode::animation() {
        return _animations;
    }

    void FireAnimationNode::addBubblesToRoot() {
        for (auto &bubbleAnimation : _bubbleAnimationNodes) {
            _root.addChild(bubbleAnimation.transNode().node());
        }
    }

    void FireAnimationNode::addAnimations() {
        for (auto &bubbleAnimation : _bubbleAnimationNodes) {
            _animations.add(std::shared_ptr<Animation>(
                    new AnimationContainer(bubbleAnimation.animation())
            ));
        }
    }

    float FireAnimationNode::intensity() const {
        return _intensity;
    }

    void FireAnimationNode::intensity(float intensity) {
        _intensity = magicvr::util::clamp(intensity, 0.0f, 1.0f);
        node().scale(_intensity);
    }

}}