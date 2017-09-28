#include "magicvr/node/TrajectoryNode.hpp"
#include "magicvr/node/node.hpp"

namespace magicvr { namespace node {
    using namespace OSG;

    NodeTransitPtr TrajectoryNode::node() {
        if (_node == nullptr) {
            _node = makeNodeFor(Group::create());
        }
        return NodeTransitPtr(_node);
    }

    void TrajectoryNode::add(const Vec3f &point) {
        if (node()->getNChildren() == 0) {
            _node->addChild(pointNode(point));
            _previousPoint = point;
        } else if (_previousPoint != point) {
            _node->addChild(lineNode(_previousPoint, point));
            _node->addChild(pointNode(point));
            _previousPoint = point;
        }
    }

    void TrajectoryNode::clear() {
        _node->clearChildren();
    }

}}
