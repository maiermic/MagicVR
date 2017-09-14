#ifndef MYPROJECT_TRACKER_H
#define MYPROJECT_TRACKER_H


#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>

OSG_USING_NAMESPACE


namespace input {
    struct Tracker {
        Vec3f position;
        Quaternion orientation;
    };
}


#endif //MYPROJECT_TRACKER_H
