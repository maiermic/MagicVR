#pragma once

#include <OpenSG/OSGVector.h>
#include <OpenSG/OSGQuaternion.h>
#include <range/v3/view/transform.hpp>

namespace magicvr { namespace ranges { namespace view {

    inline auto rotate(OSG::Quaternion rotation) {
        return [=](std::vector<OSG::Vec3f> &&trajectory) {
            OSG::Matrix4f mat;
            mat.setRotate(rotation);
            return trajectory |
                   ::ranges::view::transform([=](OSG::Vec3f v) {
                       return mat * v;
                   }) |
                   ::ranges::to_vector;
        };
    }

}}}
