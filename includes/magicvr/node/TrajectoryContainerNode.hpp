#ifndef MAGICVR_NODE_TRAJECTORY_CONTAINER_NODE_HPP
#define MAGICVR_NODE_TRAJECTORY_CONTAINER_NODE_HPP

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGNode.h>
#include <vector>
#include "TrajectoryNode.hpp"

namespace magicvr { namespace node {

    class TrajectoryContainerNode {
        TrajectoryNode _node;
        std::vector<OSG::Vec3f> _trajectory;
    public:
        void add(const OSG::Vec3f &point);

        void clear();

        OSG::NodeTransitPtr node();

        std::vector<OSG::Vec3f> &trajectory();

        void update();

        TrajectoryContainerNode();

        TrajectoryContainerNode(std::vector<OSG::Vec3f> &&vector);
    };

}}

#endif //MAGICVR_NODE_TRAJECTORY_CONTAINER_NODE_HPP
