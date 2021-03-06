#include <range/v3/utility/functional.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/to_container.hpp>
#include "magicvr/animation/BubblesAnimationNode.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <magicvr/animation/Animation.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include <magicvr/animation/ScaleAnimation.hpp>

namespace magicvr { namespace animation {

    BubblesAnimationNode::BubblesAnimationNode(
            Path modelPath,
            const std::vector<BubbleData> &bubbleDatas
    ) : _bubbleDatas(details::buildBubbleDatas(modelPath, bubbleDatas)),
        _animations(false) {
        addBubblesToRoot();
        addAnimations();
    }

    void BubblesAnimationNode::addBubblesToRoot() {
        for (const auto &data : _bubbleDatas) {
            _root.addChild(data.node);
        }
    }

    void BubblesAnimationNode::addAnimations() {
        for (const auto &data : _bubbleDatas) {
            _animations.add(std::shared_ptr<Animation>(
                    new ParallelAnimation{
                            std::shared_ptr<Animation>(
                                    new TranslationAnimation(
                                            data.transformation,
                                            OSG::Vec3f(0, 1, 0),
                                            3 * data.data, true)),

                            std::shared_ptr<Animation>(
                                    new ScaleAnimation(
                                            data.transformation,
                                            OSG::Vec3f(0, 0, 0),
                                            3 * data.data, true))
                    }
            ));
        }
    }

    const OSG::NodeTransitPtr
    details::buildBubble(OSG::ComponentTransformRecPtr transCT,
                                      OSG::NodeRecPtr model, float size) {
        return ComponentTransformNode(transCT)
                .scale(size)
                .addChild(OSG::NodeTransitPtr(model))
                .node();
    }

    std::vector<details::InternalBubbleData>
    details::buildBubbleDatas(
            Path modelPath,
            const std::vector<BubbleData> &bubbleDatas) {
        return bubbleDatas |
               ::ranges::view::transform([=](const BubbleData &data) {
                   const OSG::ComponentTransformRecPtr transformation =
                           OSG::ComponentTransformBase::create();
                   const auto model =
                           OSG::SingletonHolder<OSG::SceneFileHandlerBase>::the()
                                   ->read(modelPath);
                   return details::InternalBubbleData (
                           data,
                           transformation,
                           buildBubble(transformation, model, data)
                   );
               }) |
               ::ranges::to_vector;
    }

    ComponentTransformNode BubblesAnimationNode::transNode() {
        return _root;
    }

    const ComponentTransformNode BubblesAnimationNode::transNode() const {
        return _root;
    }

    Animation &BubblesAnimationNode::animation() {
        return _animations;
    }

    OSG::NodeRecPtr BubblesAnimationNode::node() {
        return transNode().node();
    }

    const OSG::NodeRecPtr BubblesAnimationNode::node() const {
        return transNode().node();
    }

    details::InternalBubbleData::InternalBubbleData(BubbleData data,
                                                    OSG::ComponentTransformRecPtr transformation,
                                                    OSG::NodeRecPtr node)
            : data(data), transformation(transformation), node(node) {}
}}