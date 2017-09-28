#ifndef MAGICVR_NODE_INDEX_FINGER_TIP_HPP
#define MAGICVR_NODE_INDEX_FINGER_TIP_HPP

#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGNode.h>
#include <Leap/Leap.h>


namespace magicvr { namespace node {

    class IndexFingerTip {
        Leap::Controller &_controller;
        OSG::ComponentTransformRecPtr _transformer;
        OSG::NodeRecPtr _node;

        void onIndexFinger(const Leap::Finger &);
    public:
        IndexFingerTip(Leap::Controller &);

        OSG::NodeTransitPtr node();

        void update();
    };

}}

#endif //MAGICVR_NODE_INDEX_FINGER_TIP_HPP
