#ifndef MAGICVR_NODE_TRAJECTORY_NODE_HPP
#define MAGICVR_NODE_TRAJECTORY_NODE_HPP

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGNode.h>

namespace magicvr { namespace node {

    class TrajectoryNode {
    public:
        void add(const OSG::Vec3f &point);

        void clear();

        OSG::NodeTransitPtr node();

    private:
        OSG::NodeRecPtr _node;
        OSG::Vec3f _previousPoint;
    };

}}

#endif //MAGICVR_NODE_TRAJECTORY_NODE_HPP
