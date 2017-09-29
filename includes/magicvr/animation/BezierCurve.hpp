#ifndef MAGICVR_BEZIERCURVE_HPP
#define MAGICVR_BEZIERCURVE_HPP

#include <OpenSG/OSGVector.h>

template<class Vector = typename OSG::Vec3f>
class BezierCurve {
    using Percentage = typename Vector::ValueType;

    const std::vector<Vector> _points;

    static Vector getPt(Vector n1, Vector n2, Percentage perc) {
        return n1 + ((n2 - n1) * perc);
    }

public:
    BezierCurve(std::initializer_list<Vector> points)
            : _points(points) {}

    Vector atPercentage(Percentage percentage) const {
        auto ps = _points;
        while (ps.size() > 1) {
            Vector previous = ps.front();
            for (std::size_t i = 1; i < ps.size(); ++i) {
                const Vector current = ps.at(i);
                ps.at(i - 1) = getPt(previous, current, percentage);
                previous = current;
            }
            ps.pop_back();
        }
        return ps.front();
    }

};


#endif //MAGICVR_BEZIERCURVE_HPP
