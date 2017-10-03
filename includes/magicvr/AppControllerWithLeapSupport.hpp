#ifndef MAGICVR_APPCONTROLLERWITHLEAPSUPPORT_HPP
#define MAGICVR_APPCONTROLLERWITHLEAPSUPPORT_HPP


#include <magicvr/leap/FingerTipPosition.hpp>
#include <magicvr/util/VectorConverter.hpp>
#include <magicvr/node/MovableNode.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include "AppController.hpp"
#include "MagicTricks.hpp"

namespace magicvr {
    class AppControllerWithLeapSupport : public AppController {
        leap::FingerTipPosition _indexFingerTipPosition;
        node::MovableNode _indexFingerTipNode;
        node::TrajectoryContainerNode _trajectoryNode;
        util::VectorConverter _vectorConverter;
        bool _isRecordingTrajectory;
        MagicTricks _tricks;

        NodeTransitPtr createIndexFingerTipNode();

    public:
        AppControllerWithLeapSupport(
                const leap::FingerTipPosition &_indexFingerTipPosition);

        void display(OSG::Time dTime) override;

        void keyboardDown(unsigned char key, int x, int y) override;

        void keyboardUp(unsigned char key, int x, int y) override;

    };
}

#endif //MAGICVR_APPCONTROLLERWITHLEAPSUPPORT_HPP
