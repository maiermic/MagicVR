#ifndef MAGICVR_MODEL_HPP
#define MAGICVR_MODEL_HPP

#include <vector>
#include <OpenSG/OSGVector.h>

namespace magicvr { namespace model {
    using point = OSG::Vec3f;
    using point_2d = OSG::Vec2f;
    using trajectory = std::vector<point>;
    using trajectory_2d = std::vector<point_2d>;
}}

#endif //MAGICVR_MODEL_HPP
