#include "magicvr/util/VectorConverter.hpp"

namespace magicvr { namespace util {

    OSG::Vec3f toVec3f(const Leap::Vector &lv) {
        return OSG::Vec3f(lv.x, lv.y, lv.z);
    }
    
    VectorConverter::VectorConverter()
            : _leapZeroPoint(0, -100, 0), _movementPercision(5) {}

    OSG::Vec3f VectorConverter::toVec3f(const Leap::Vector &vector) {
        return (magicvr::util::toVec3f(vector) + _leapZeroPoint) /
               _movementPercision;
    }
}}