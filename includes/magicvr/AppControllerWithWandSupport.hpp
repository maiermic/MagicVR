#ifndef MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP
#define MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP


#include <magicvr/util/VectorConverter.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <input/RemoteManager.hpp>
#include "AppController.hpp"

namespace magicvr {
    class AppControllerWithWandSupport : public AppController {
        node::MovableNode _movableNode;
        node::TrajectoryContainerNode _trajectoryNode;
        input::RemoteManager &_wand;

        NodeTransitPtr createMovableNode();

    public:
        AppControllerWithWandSupport(input::RemoteManager &wand);

        void display(OSG::Time dTime) override;

        void keyboardDown(unsigned char key, int x, int y) override;
    };
}

#endif //MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP
