#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <magicvr/animation/ParallelAnimation.hpp>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>

OSG_USING_NAMESPACE

class Scene {
    const NodeRecPtr _root;
    const ComponentTransformRecPtr earthUnlockedCT;
    const ComponentTransformRecPtr fireUnlockedCT;
    const ComponentTransformRecPtr waterUnlockedCT;
    const ComponentTransformRecPtr thunderUnlockedCT;

    const ComponentTransformRecPtr fireBubbleCT1;
    const ComponentTransformRecPtr fireBubbleCT2;
    const ComponentTransformRecPtr fireBubbleCT3;
    const ComponentTransformRecPtr fireBubbleCT4;
    const ComponentTransformRecPtr fireBubbleCT5;
    const ComponentTransformRecPtr fireBubbleCT6;
    const ComponentTransformRecPtr fireBubbleCT7;
    const ComponentTransformRecPtr fireBubbleCT8;

    const ComponentTransformRecPtr waterBubbleCT1;
    const ComponentTransformRecPtr waterBubbleCT2;
    const ComponentTransformRecPtr waterBubbleCT3;
    const ComponentTransformRecPtr waterBubbleCT4;
    const ComponentTransformRecPtr waterBubbleCT5;
    const ComponentTransformRecPtr waterBubbleCT6;
    const ComponentTransformRecPtr waterBubbleCT7;
    const ComponentTransformRecPtr waterBubbleCT8;

    const ComponentTransformRecPtr thunderBubbleCT1;
    const ComponentTransformRecPtr thunderBubbleCT2;
    const ComponentTransformRecPtr thunderBubbleCT3;
    const ComponentTransformRecPtr thunderBubbleCT4;
    const ComponentTransformRecPtr thunderBubbleCT5;
    const ComponentTransformRecPtr thunderBubbleCT6;
    const ComponentTransformRecPtr thunderBubbleCT7;
    const ComponentTransformRecPtr thunderBubbleCT8;

    const ComponentTransformRecPtr earthBubbleCT1;
    const ComponentTransformRecPtr earthBubbleCT2;
    const ComponentTransformRecPtr earthBubbleCT3;
    const ComponentTransformRecPtr earthBubbleCT4;
    const ComponentTransformRecPtr earthBubbleCT5;
    const ComponentTransformRecPtr earthBubbleCT6;
    const ComponentTransformRecPtr earthBubbleCT7;
    const ComponentTransformRecPtr earthBubbleCT8;


    ParallelAnimation _animations;

    void build();

    const NodeTransitPtr buildElement(const ComponentTransformRecPtr trans,
                                      const char *modelName) const;

    const NodeTransitPtr buildEarthElement() const;

    const NodeTransitPtr buildEarthElementalStone() const;

    const NodeTransitPtr buildFireElement() const;

    const NodeTransitPtr buildFireElementalStone() const;

    const NodeTransitPtr buildWaterElement() const;

    const NodeTransitPtr buildWaterElementalStone() const;

    const NodeTransitPtr buildThunderElement() const;

    const NodeTransitPtr buildThunderElementalStone() const;

    const NodeTransitPtr buildBackLeftPedestal() const;

    const NodeTransitPtr buildBackRightPedestal() const;

    const NodeTransitPtr buildFrontLeftPedestal() const;

    const NodeTransitPtr buildFrontRightPedestal() const;

    const NodeRecPtr buildRealWorldScale() const;

    void unlockElement(const ComponentTransformRecPtr elementCT);

    ComponentTransformNode buildPedestal() const;

public:

    Scene();

    void update(OSG::Time dTime);

    const NodeRecPtr &root() const;

    void unlockEarth();

    void unlockFire();

    void unlockWater();

    void unlockThunder();

    NodeTransitPtr buildBezierCurve() const;
    const NodeRecPtr buildTest() const;

    const NodeTransitPtr buildBubble() const;

    void animateFireBubbles();

    const NodeTransitPtr buildFireBubble1() const;

    const NodeTransitPtr buildBubbles() const;

    const NodeTransitPtr buildFireBubble8() const;

    const NodeTransitPtr buildFireBubble7() const;

    const NodeTransitPtr buildFireBubble6() const;

    const NodeTransitPtr buildFireBubble5() const;

    const NodeTransitPtr buildFireBubble2() const;

    const NodeTransitPtr buildFireBubble3() const;

    const NodeTransitPtr buildFireBubble4() const;

    const NodeTransitPtr buildFireBubbles() const;

    const NodeTransitPtr buildWaterBubbles() const;

    const NodeTransitPtr buildThunderBubbles() const;

    const NodeTransitPtr buildEarthBubbles() const;

    const NodeTransitPtr buildWaterBubble1() const;

    const NodeTransitPtr buildWaterBubble2() const;

    const NodeTransitPtr buildWaterBubble3() const;

    const NodeTransitPtr buildWaterBubble4() const;

    const NodeTransitPtr buildWaterBubble5() const;

    const NodeTransitPtr buildWaterBubble6() const;

    const NodeTransitPtr buildWaterBubble7() const;

    const NodeTransitPtr buildWaterBubble8() const;

    const NodeTransitPtr buildThunderBubble8() const;

    const NodeTransitPtr buildThunderBubble7() const;

    const NodeTransitPtr buildThunderBubble6() const;

    const NodeTransitPtr buildThunderBubble5() const;

    const NodeTransitPtr buildThunderBubble4() const;

    const NodeTransitPtr buildThunderBubble3() const;

    const NodeTransitPtr buildThunderBubble2() const;

    const NodeTransitPtr buildThunderBubble1() const;

    const NodeTransitPtr buildEarthBubble8() const;

    const NodeTransitPtr buildEarthBubble7() const;

    const NodeTransitPtr buildEarthBubble6() const;

    const NodeTransitPtr buildEarthBubble5() const;

    const NodeTransitPtr buildEarthBubble4() const;

    const NodeTransitPtr buildEarthBubble3() const;

    const NodeTransitPtr buildEarthBubble2() const;

    const NodeTransitPtr buildEarthBubble1() const;

    void animateWaterBubbles();

    void animateThunderBubbles();

    void animateEarthBubbles();
};


#endif //MYPROJECT_BASESCENE_H
