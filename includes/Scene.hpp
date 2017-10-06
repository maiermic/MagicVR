#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <magicvr/animation/ParallelAnimation.hpp>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <input/Tracker.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/animation/BubbleAnimationsNode.hpp>
#include <magicvr/animation/FireAnimationNode.hpp>
#include <magicvr/ranges/view/range.hpp>
#include <magicvr/animation/AnimationChildNode.hpp>
#include "PathSettings.hpp"

OSG_USING_NAMESPACE

class Scene {
    using AnimationChildNodePtr = std::shared_ptr<magicvr::animation::AnimationChildNode>;
    const NodeRecPtr _root;

    magicvr::node::TrajectoryContainerNode _inputTrajectoryNode;
    magicvr::node::TrajectoryContainerNode _preprocessedInputTrajectoryNode;
    magicvr::node::TrajectoryContainerNode _patternTrajectoryNode;

    ComponentTransformNode _windElementalStone;

//    const ComponentTransformRecPtr earthUnlockedCT;
//    const ComponentTransformRecPtr fireUnlockedCT;
//    const ComponentTransformRecPtr waterUnlockedCT;
//    const ComponentTransformRecPtr thunderUnlockedCT;

    magicvr::animation::FireAnimationNode _fire;

    magicvr::animation::BubbleAnimationsNode _fireBubbles;
    magicvr::animation::BubbleAnimationsNode _waterBubbles;
    magicvr::animation::BubbleAnimationsNode _thunderBubbles;
    AnimationChildNodePtr _windBubbles;

    const ComponentTransformRecPtr lightBubbleCT;




    ParallelAnimation _animations;

    void build();

    const NodeTransitPtr buildStonehenge() const;

//    const NodeTransitPtr buildElement(const ComponentTransformRecPtr trans,
//                                      const char *modelName) const;

//    const NodeTransitPtr buildEarthElement() const;

    static ComponentTransformNode createWindElementalStone();

//    const NodeTransitPtr buildFireElement() const;

    const NodeTransitPtr buildFireElementalStone() const;

//    const NodeTransitPtr buildWaterElement() const;

    const NodeTransitPtr buildWaterElementalStone() const;

//    const NodeTransitPtr buildThunderElement() const;

    const NodeTransitPtr buildThunderElementalStone() const;

    const NodeTransitPtr buildBackLeftPedestal() const;

    const NodeTransitPtr buildBackRightPedestal() const;

    const NodeTransitPtr buildFrontLeftPedestal() const;

    const NodeTransitPtr buildFrontRightPedestal() const;

    const NodeRecPtr buildRealWorldScale();

    const NodeTransitPtr buildLightBubble() const;

    const NodeTransitPtr buildPedestal() const;

public:

    Scene();

//    void unlockEarth();
//
//    void unlockFire();
//
//    void unlockWater();
//

    void update(OSG::Time dTime);

    const NodeRecPtr &root() const;

    magicvr::animation::FireAnimationNode& fire();

//    void unlockThunder();

    NodeTransitPtr buildBezierCurve() const;


//    const NodeTransitPtr buildBubble() const;

    void animateFire();

    void animateFireBubbles();

    void animateWaterBubbles();

    void animateThunderBubbles();

    void animateWindBubbles();

    void stopAnimateWindBubbles();

    const NodeTransitPtr buildKapelle() const;


    const NodeTransitPtr buildLantern() const;

    NodeTransitPtr buildSpiral() const;

    void shootLight(input::Tracker wand, Vec3f destination);

    const NodeTransitPtr buildScenesModels();

    void showInputTrajectory(std::vector<OSG::Vec3f> &&trajectory);

    void showPreprocessedInputTrajectory(std::vector<OSG::Vec3f> &&trajectory);

    void showPatternTrajectory(std::vector<OSG::Vec3f> &&trajectory);

    static magicvr::animation::BubbleAnimationsNode createFireBubbles();

    static magicvr::animation::BubbleAnimationsNode createWaterBubbles();

    static std::shared_ptr<magicvr::animation::BubbleAnimationsNode>
    createWindBubbles();

    static magicvr::animation::BubbleAnimationsNode createThunderBubbles();

    static std::vector<float> getBubblesRange();
};


#endif //MYPROJECT_BASESCENE_H
