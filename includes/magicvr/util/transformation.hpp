#ifndef MAGICVR_UTIL_TRANSFORMATION_HPP
#define MAGICVR_UTIL_TRANSFORMATION_HPP

#include <OpenSG/OSGNode.h>

namespace magicvr { namespace util {
    OSG::NodeTransitPtr
    translateNode(const OSG::NodeRecPtr node, const OSG::Vec3f translation);
}}

#endif //TUTORIALS_TRANSFORMATION_HPP
