#ifndef MYPROJECT_UTIL_H
#define MYPROJECT_UTIL_H

#include <vrpn_LUDL.h>
#include <OpenSG/OSGGL.h>
#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGQuaternion.h>


namespace util {
    OSG::QuaternionBase<OSG::Real32> arrayToQuaternion(const vrpn_float64 *array);
}

#endif //MYPROJECT_UTIL_H
