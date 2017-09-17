#include "util.hpp"


OSG::QuaternionBase<OSG::Real32> util::arrayToQuaternion(const vrpn_float64 *array) {
    return OSG::Quaternion(array[0], array[1], array[2], array[3]);
}
