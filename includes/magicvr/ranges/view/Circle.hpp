#pragma once

#include <vector>
#include <OpenSG/OSGVector.h>
#include "range.hpp"

namespace magicvr { namespace ranges { namespace view {

    class Circle {
        const float _radius;
    public:
        explicit Circle(float radius);

        inline float x(float angleDegree) const {
            return std::cos(OSG::osgDegree2Rad(angleDegree)) * _radius;
        }

        inline float y(float angleDegree) const {
            return -std::sin(OSG::osgDegree2Rad(angleDegree)) * _radius;
        }

        inline auto
        sample(float startAngle, float endAngle, float angleStep) const {
            namespace rv = ::ranges::view;
            return range(startAngle, endAngle, angleStep) |
                   rv::transform([&](float angle) {
                       return OSG::Vec2f(x(angle), y(angle));
                   });
        }
    };

}}}

