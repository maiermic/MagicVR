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
    const ComponentTransformRecPtr torusCT;
    const ComponentTransformRecPtr cylinderCT;
    const SwitchRecPtr switchBox;
    const input::Tracker &wand;

    void build();

public:
    const NodeRecPtr root = Node::create();

    Scene(input::Tracker &wand);

    void update();

    void showBox(bool isVisible);
};


#endif //MYPROJECT_BASESCENE_H
