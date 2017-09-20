#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransformBase.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <OpenSG/OSGSwitchFields.h>
#include <OpenSG/OSGSwitch.h>
#include <OpenSG/OSGSimpleGeometry.h>

#include "input/Tracker.hpp"

OSG_USING_NAMESPACE


class Scene {
    const ComponentTransformRecPtr torusCT = ComponentTransformBase::create();
    const ComponentTransformRecPtr cylinderCT = ComponentTransformBase::create();
    const SwitchRecPtr switchBox = SwitchBase::create();
    const input::Tracker &wand;

    void build();

public:
    const NodeRecPtr root = Node::create();

    Scene(input::Tracker &wand)
            : wand(wand) {
        build();
        update();
    }

    ~Scene() {}

    void update();

    void showBox(bool isVisible);
};


#endif //MYPROJECT_BASESCENE_H
