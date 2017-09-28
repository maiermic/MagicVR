#ifndef MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP
#define MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP


#include <magicvr/util/VectorConverter.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <input/Tracker.hpp>
#include "AppController.hpp"

namespace magicvr {
    class AppControllerWithWandSupport : public AppController {
        node::MovableNode _movableNode;
        node::TrajectoryContainerNode _trajectoryNode;
        bool _isRecordingTrajectory;
        input::Tracker &_wand;

        NodeTransitPtr createMovableNode();

    public:
        AppControllerWithWandSupport(input::Tracker &wand);

        void display(OSG::Time dTime) override;
    };
}

#endif //MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP
