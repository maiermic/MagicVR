#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <magicvr/animation/BezierAnimation.hpp>
#include <magicvr/animation/EaseInOutAnimation.hpp>
#include <magicvr/Spiral.hpp>
#include <range/v3/to_container.hpp>
#include <magicvr/ranges/view/Circle.hpp>
#include <magicvr/ranges/view/rotate.hpp>
#include <magicvr/animation/ScaleAnimation.hpp>
#include <magicvr/animation/SequentialAnimation.hpp>
#include "PathSettings.hpp"
#include <magicvr/animation/BezierTranslationAnimation.hpp>
#include <input/Tracker.hpp>
#include <OpenSG/OSGSimpleGeometry.h>
#include <magicvr/animation/AnimationContainer.hpp>
#include <magicvr/animation/OnStopAnimation.hpp>
#include <magicvr/animation/AnimationChildNode.hpp>
#include <magicvr/animation/MaxTimeAnimation.hpp>
#include <magicvr/animation/BezierTranslationAnimationNode.hpp>
#include <magicvr/animation/OnStopRefAnimation.hpp>

void Scene::build() {
    root()->addChild(_realWorldScale);
//    root()->addChild(buildBezierCurve());
//    root()->addChild(buildSpiral());

    ComponentTransformNode trajectoryNodes;
    trajectoryNodes.translate(0, 200, -100);

    const SimpleMaterialRecPtr red_material = OSG::SimpleMaterialBase::create();
    red_material->setDiffuse(Color3f(1, 0.4f, 0));
    red_material->setAmbient(Color3f(0.8f, 0.2f, 0.2f));
    const MaterialGroupRecPtr red_material_group = MaterialGroupBase::create();
    red_material_group->setMaterial(red_material);
    const NodeTransitPtr pattern_trajectory_node_with_material = makeNodeFor(
            red_material_group);
    pattern_trajectory_node_with_material->addChild(
            _patternTrajectoryNode.node());
    trajectoryNodes.addChild(pattern_trajectory_node_with_material);

    const SimpleMaterialRecPtr green_material = OSG::SimpleMaterialBase::create();
    green_material->setDiffuse(Color3f(0, 1, 0.8f));
    green_material->setAmbient(Color3f(0.2f, 0.8f, 0.2f));
    const MaterialGroupRecPtr green_material_group = MaterialGroupBase::create();
    green_material_group->setMaterial(green_material);
    const NodeTransitPtr input_trajectory_node_with_material = makeNodeFor(
            green_material_group);
    input_trajectory_node_with_material->addChild(_inputTrajectoryNode.node());
    trajectoryNodes.addChild(input_trajectory_node_with_material);

    trajectoryNodes.addChild(_preprocessedInputTrajectoryNode.node());
//    root()->addChild(_inputTrajectoryNode.node());
//    root()->addChild(_patternTrajectoryNode.node());
//    root()->addChild(trajectoryNodes.node());

    auto c =
            magicvr::ranges::view::Circle(100).sample(0, 360, 10) |
            ranges::view::transform([](OSG::Vec2f v) {
                return OSG::Vec3f(v.x(), v.y(), 0);
            }) |
            magicvr::ranges::view::rotate(
                    OSG::Quaternion(
                            OSG::Vec3f(0.f, 1.f, 0.f),
                            OSG::osgDegree2Rad(90)
                    )
            ) |
            ranges::to_vector;
//    root()->addChild(
//            magicvr::node::TrajectoryContainerNode(std::move(c)).node()
//    );
}

const NodeTransitPtr Scene::buildStonehenge() const {
    return ComponentTransformNode()
            .translate(-1.5f, 0, -0.5f)
            .scale(1)
//            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(0)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_NewStonehenge))
            .addChild(_fire.node().node())
            .node();
}

const NodeTransitPtr Scene::buildLantern() const {
    return ComponentTransformNode()
            .translate(0, 0, 0)
            .scale(0.1f)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_Lantern))
            .node();
}

const NodeTransitPtr Scene::buildKapelle() const {
    return ComponentTransformNode()
            /* TODO: Decide for position
             * */
//            .translate(0,-0.17f,1.8)
            .translate(0, -0.35f, 5)
            .scale(12)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(90)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_Kapelle))
            .node();
}

void Scene::animateFire() {
    _animations.add(std::shared_ptr<Animation>(
            new AnimationContainer(_fire.animation())
    ));
}

void Scene::animateFireBubbles() {
    animateBubbles(_fireBubbles,
                   Path_Model_FireBubble,
                   _fireElementalStone.node());
}

void Scene::animateWaterBubbles() {
    animateBubbles(_waterBubbles,
                   Path_Model_WaterBubble,
                   _waterElementalStone.node());
}

void Scene::animateThunderBubbles() {
    animateBubbles(_thunderBubbles,
                   Path_Model_ThunderBubble,
                   _thunderElementalStone.node());
}

void Scene::stopAnimateBubbles(Scene::AnimationPtr &bubbles) {
    if (bubbles) {
        bubbles->stop();
        bubbles = nullptr;
    }
}

void Scene::stopAnimateFireBubbles() {
    stopAnimateBubbles(_fireBubbles);
}

void Scene::stopAnimateWaterBubbles() {
    stopAnimateBubbles(_waterBubbles);
}

void Scene::stopAnimateThunderBubbles() {
    stopAnimateBubbles(_thunderBubbles);
}

void Scene::stopAnimateWindBubbles() {
    stopAnimateBubbles(_windBubbles);
}

void Scene::animateBubbles(AnimationPtr &bubbles,
                           Path modelPath,
                           OSG::NodeTransitPtr elementalStoneNode) {
    using namespace magicvr::animation;
    if (areBubblesRunning(bubbles)) {
        return;
    }
    bubbles = AnimationPtr(
            new MaxTimeAnimation(
                    10,
                    AnimationPtr(
                            new AnimationChildNode(
                                    elementalStoneNode,
                                    createBubblesAnimationNode(modelPath)
                            )
                    )
            )
    );
    _animations.add(bubbles);
}

bool Scene::areBubblesRunning(const Scene::AnimationPtr bubbles) const {
    return bubbles && !bubbles->isStopped();
}

void Scene::animateWindBubbles() {
    animateBubbles(_windBubbles,
                   Path_Model_WindBubble,
                   _windElementalStone.node());
}

void Scene::shootLight(input::Tracker wand, OSG::Vec3f destination) {
    using namespace magicvr::animation;
    _animations.add(std::shared_ptr<Animation>(
            new OnStopRefAnimation(
                    std::shared_ptr<Animation>(
                            new AnimationChildNode(
                                    _realWorldScale,
                                    std::shared_ptr<AnimationNode>(
                                            new BezierTranslationAnimationNode(
                                                    buildLightBubble(),
                                                    getShootingCurve(wand,
                                                                     destination),
                                                    3
                                            )
                                    )
                            )
                    ), []() {
                        std::cout << "shooted light reached destination\n";
                    })
    ));
}

void Scene::shootWater(input::Tracker wand, OSG::Vec3f destination) {
    using namespace magicvr::animation;
    _animations.add(std::shared_ptr<Animation>(
            new OnStopRefAnimation(
                    std::shared_ptr<Animation>(
                            new AnimationChildNode(
                                    _realWorldScale,
                                    std::shared_ptr<AnimationNode>(
                                            new BezierTranslationAnimationNode(
                                                    buildWaterBubble(),
                                                    getShootingCurve(wand,
                                                                     destination),
                                                    3
                                            )
                                    )
                            )
                    ), []() {
                        std::cout << "shooted water reached destination\n";
                    })
    ));
}

BezierCurve<> Scene::getShootingCurve(input::Tracker wand, OSG::Vec3f destination) {
    using namespace magicvr::animation;

    OSG::Vec3f wandDirection;
    wand.orientation.multVec(OSG::Vec3f(0, 0, -1), wandDirection);
    wandDirection.normalize();

    auto worldWandPosition = wand.position / 100;
    return BezierCurve<> {
            worldWandPosition,
            worldWandPosition + wandDirection,
            destination,
            destination
    };
}


const NodeRecPtr Scene::buildRealWorldScale() {
    /** realWorldScale
     *
     * Models exported from Blender are interpreted to SMALL by the
     * OSGFileHandler about the factor 100.
     *
     * -> Scale the whole scene up by 100
     *
     * => read/write future Translation as 1 = 1meter
     * => read/write future Scale as 1 = 100% */

    /**
     * Since we have a not working Beamer on the right side
     * of the cave, meanwhile turn the complete scene about 30° to the left */
    return ComponentTransformNode()
//            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .scale(100)
            .addChild(buildScenesModels())
            .node();
}

const NodeTransitPtr Scene::buildScenesModels() {
    return ComponentTransformNode()
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .addChild(_stonehenge)
//            .addChild(buildLantern())
//            .addChild(buildKapelle())
            .addChild(buildFrontLeftPedestal())
            .addChild(buildFrontRightPedestal())
            .addChild(buildBackLeftPedestal())
            .addChild(buildBackRightPedestal())
            .node();
}


const NodeTransitPtr Scene::buildPedestal() const {
    return ComponentTransformNode()
            .scale(0.5, 1, 0.5)
            .addChild(
                    SingletonHolder<SceneFileHandlerBase>::the()
                            ->read(Path_Model_Sockel))
            .node();
}


const NodeTransitPtr Scene::buildFrontLeftPedestal() const {
    return ComponentTransformNode()
            .translate(-0.4f, 0, -1.05f)
            .addChild(buildPedestal())
            .addChild(_waterElementalStone.node())
            .node();
}

const NodeTransitPtr Scene::buildFrontRightPedestal() const {
    return ComponentTransformNode()
            .translate(1.25f, 0, -0.8f)
            .addChild(buildPedestal())
            .addChild(_fireElementalStone.node())
            .node();
}

const NodeTransitPtr Scene::buildBackLeftPedestal() const {
    return ComponentTransformNode()
            .translate(-1.25f, -0.15f, -1.8f)
            .addChild(buildPedestal())
            .addChild(_windElementalStone.node())
            .node();
}

const NodeTransitPtr Scene::buildBackRightPedestal() const {
    return ComponentTransformNode()
            .translate(0.4f, 0, -0.75f)
            .addChild(buildPedestal())
            .addChild(_thunderElementalStone.node())
            .node();
}

ComponentTransformNode
Scene::createElementalStone(Path modelPath, float rotationAngle) {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(1)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(rotationAngle)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    modelPath));
}


void Scene::update(OSG::Time dTime) {
    _animations.animate(dTime);
}

Scene::Scene()
        : _animations(ParallelAnimation::DO_NOT_STOP_IF_NO_ANIMATIONS),
          _root(makeNodeFor(Group::create())),
          _windElementalStone(createElementalStone(Path_Model_WindStone, 30)),
          _fireElementalStone(createElementalStone(Path_Model_FireStone, -30)),
          _waterElementalStone(createElementalStone(Path_Model_WaterStone, 30)),
          _thunderElementalStone(createElementalStone(Path_Model_ThunderStone, -30)),
          _fireBubbles(nullptr),
          _waterBubbles(nullptr),
          _thunderBubbles(nullptr),
          _windBubbles(nullptr) {
    _stonehenge = buildStonehenge();
    _realWorldScale = buildRealWorldScale();
    build();
    update(0);
}

const NodeRecPtr &Scene::root() const {
    return _root;
}

NodeTransitPtr Scene::buildBezierCurve() const {
    const BezierCurve<> bezier{
            {0,   0,   0},
            {75,  0,   0},
            {25,  100, 0},
            {100, 100, 0}
    };
    return magicvr::node::TrajectoryContainerNode(bezier.sample(21)).node();
}

NodeTransitPtr Scene::buildSpiral() const {
    return magicvr::node::TrajectoryContainerNode(Spiral().sample()).node();
}


ComponentTransformNode Scene::buildLightBubble() const {
    return ComponentTransformNode()
            .scale(0.8f)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble));
}

ComponentTransformNode Scene::buildWaterBubble() const {
    return ComponentTransformNode()
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble));
}

void Scene::showInputTrajectory(std::vector<OSG::Vec3f> &&trajectory) {
    _inputTrajectoryNode.trajectory() = trajectory;
    _inputTrajectoryNode.update();
}

void Scene::showPreprocessedInputTrajectory(
        std::vector<OSG::Vec3f> &&trajectory) {
    _preprocessedInputTrajectoryNode.trajectory() = trajectory;
    _preprocessedInputTrajectoryNode.update();
}

void Scene::showPatternTrajectory(std::vector<OSG::Vec3f> &&trajectory) {
    _patternTrajectoryNode.trajectory() = trajectory;
    _patternTrajectoryNode.update();
}

magicvr::animation::FireAnimationNode &Scene::fire() {
    return _fire;
}

std::shared_ptr<magicvr::animation::BubblesAnimationNode>
Scene::createBubblesAnimationNode(Path modelPath) {
    return std::shared_ptr<magicvr::animation::BubblesAnimationNode>(
            new magicvr::animation::BubblesAnimationNode(
                    modelPath,
                    getBubblesRange()
            )
    );
}

std::vector<float> Scene::getBubblesRange() {
    return magicvr::ranges::view::rangeV(0.3f, 1.0f, 0.1f);
}
