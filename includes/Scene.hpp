#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <magicvr/animation/Animations.hpp>
#include <magicvr/ComponentTransformNode.hpp>

OSG_USING_NAMESPACE

class Scene {
    const NodeRecPtr _root;
    const ComponentTransformRecPtr earthUnlockedCT;
    const ComponentTransformRecPtr fireUnlockedCT;
    const ComponentTransformRecPtr waterUnlockedCT;
    const ComponentTransformRecPtr thunderUnlockedCT;
    Animations _animations;

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

    void update(float dTime);

    const NodeRecPtr &root() const;

    void unlockEarth();

    void unlockFire();

    void unlockWater();

    void unlockThunder();
};


#endif //MYPROJECT_BASESCENE_H
