#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>

OSG_USING_NAMESPACE

class Scene {
    const NodeRecPtr _root;
    const ComponentTransformRecPtr waterUnlockedCT;

    void build();
public:

    Scene();

    void update();

    const NodeRecPtr &root() const;

    const NodeTransitPtr buildWaterElementalStone() const;
};


#endif //MYPROJECT_BASESCENE_H
