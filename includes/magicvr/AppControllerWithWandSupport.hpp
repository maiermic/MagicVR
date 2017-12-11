#ifndef MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP
#define MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP


#include <magicvr/util/VectorConverter.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <input/RemoteManager.hpp>
#include "AppController.hpp"

namespace magicvr {
    class AppControllerWithWandSupport : public AppController {
        input::RemoteManager &_wand;

    public:
        explicit AppControllerWithWandSupport(input::RemoteManager &wand);

        void display(OSG::Time dTime) override;

        void keyboardDown(unsigned char key, int x, int y) override;

        void shootLight() override;

        void shootWater() override;

        void shootFire() override;
    };
}

#endif //MAGICVR_APPCONTROLLERWITHWANDSUPPORT_HPP
