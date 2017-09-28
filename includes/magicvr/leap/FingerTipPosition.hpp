#ifndef MAGICVR_LEAP_INPUT_FINGER_TIP_POSITION_HPP
#define MAGICVR_LEAP_INPUT_FINGER_TIP_POSITION_HPP


#include <Leap/Leap.h>

namespace magicvr { namespace leap {

    class FingerTipPosition {
    public:
        FingerTipPosition(Leap::Controller &, Leap::Finger::Type);

        void update();

        bool hasChanged();

        const Leap::Vector &position();

    private:
        Leap::Controller _controller;
        const Leap::Finger::Type _type;
        Leap::Vector _position;
        bool _hasChanged;
    };

}}


#endif //MAGICVR_LEAP_INPUT_FINGER_TIP_POSITION_HPP
