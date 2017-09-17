#ifndef MYPROJECT_BASESCENE_H
#define MYPROJECT_BASESCENE_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGComponentTransformFields.h>
#include <OpenSG/OSGSwitchFields.h>
#include <OpenSG/OSGSwitch.h>

#include "input/Tracker.h"

OSG_USING_NAMESPACE


class Scene {
    ComponentTransformRecPtr torusCT;
    ComponentTransformRecPtr cylinderCT;
    SwitchRecPtr switchBox;
    const input::Tracker &wand;

    void build();

public:
    NodeTransitPtr root;

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
