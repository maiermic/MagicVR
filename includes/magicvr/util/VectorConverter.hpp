#ifndef MAGICVR_UTIL_VECTOR_CONVERTER_HPP
#define MAGICVR_UTIL_VECTOR_CONVERTER_HPP

#include <OpenSG/OSGVector.h>
#include <Leap/LeapMath.h>

namespace magicvr { namespace util {

    class VectorConverter {
        OSG::Vec3f _leapZeroPoint;
        OSG::Real32 _movementPercision;

    public:
        VectorConverter();

        OSG::Vec3f toVec3f(const Leap::Vector &vector);

    };

}}

#endif //MAGICVR_UTIL_VECTOR_CONVERTER_HPP
