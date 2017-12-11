#ifndef MAGICVR_APPCONTROLLERWITHLEAPSUPPORT_HPP
#define MAGICVR_APPCONTROLLERWITHLEAPSUPPORT_HPP


#include <input/Tracker.hpp>
#include <magicvr/leap/FingerTipPosition.hpp>
#include <magicvr/util/VectorConverter.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include "AppController.hpp"

namespace magicvr {
    class AppControllerWithLeapSupport : public AppController {
        input::Tracker _wandDummy;
        leap::FingerTipPosition _indexFingerTipPosition;
        node::MovableNode _indexFingerTipNode;
        node::TrajectoryContainerNode _trajectoryNode;
        util::VectorConverter _vectorConverter;
        bool _isRecordingTrajectory;

        NodeTransitPtr createIndexFingerTipNode();

        void shootLight() override;

        void shootWater() override;

        void shootFire() override;

    public:
        AppControllerWithLeapSupport(
                const leap::FingerTipPosition &_indexFingerTipPosition);

        void display(OSG::Time dTime) override;

        void keyboardDown(unsigned char key, int x, int y) override;

        void keyboardUp(unsigned char key, int x, int y) override;

    };
}

#endif //MAGICVR_APPCONTROLLERWITHLEAPSUPPORT_HPP
