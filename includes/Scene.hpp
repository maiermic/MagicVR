#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <magicvr/animation/Animations.hpp>

OSG_USING_NAMESPACE

class Scene {
    const NodeRecPtr _root;
    const ComponentTransformRecPtr earthUnlockedCT;
    const ComponentTransformRecPtr fireUnlockedCT;
    const ComponentTransformRecPtr waterUnlockedCT;
    Animations _animations;

    void build();

    const NodeTransitPtr buildEarthElement() const;

    const NodeTransitPtr buildEarthElementalStone() const;

    const NodeTransitPtr buildFireElement() const;

    const NodeTransitPtr buildFireElementalStone() const;

    const NodeTransitPtr buildFrontRightPedestal() const;

    const NodeTransitPtr buildWaterElement() const;

    const NodeTransitPtr buildWaterElementalStone() const;

    const NodeTransitPtr buildBackLeftPedestal() const;

    const NodeTransitPtr buildFrontLeftPedestal() const;

    const NodeRecPtr buildRealWorldScale() const;

    void unlockElement(const ComponentTransformRecPtr elementCT);

public:

    Scene();

    void update(float dTime);

    const NodeRecPtr &root() const;

    void unlockEarth();

    void unlockFire();

    void unlockWater();
};


#endif //MYPROJECT_BASESCENE_H
