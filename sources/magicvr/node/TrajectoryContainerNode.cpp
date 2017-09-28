#include "magicvr/node/TrajectoryContainerNode.hpp"
#include <boost/geometry.hpp>
#include <boost/geometry/traits/point.hpp>
#include <boost/geometry/geometries/register/linestring.hpp>
BOOST_GEOMETRY_REGISTER_LINESTRING(std::vector<OSG::Vec3f>);


namespace magicvr { namespace node {
    using namespace OSG;

    void TrajectoryContainerNode::add(const Vec3f &point) {
        _node.add(point);
        boost::geometry::append(_trajectory, point);
    }

    void TrajectoryContainerNode::clear() {
        _node.clear();
        boost::geometry::clear(_trajectory);
    }

    NodeTransitPtr TrajectoryContainerNode::node() {
        return _node.node();
    }

    std::vector<Vec3f> &TrajectoryContainerNode::trajectory() {
        return _trajectory;
    }

    void TrajectoryContainerNode::update() {
        _node.clear();
        for (auto &&point : _trajectory) {
            _node.add(point);
        }
    }

}}
