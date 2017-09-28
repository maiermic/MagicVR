#include <Leap/Leap.h>
#include <magicvr/leap/FingerTipPosition.hpp>


namespace magicvr { namespace leap {

    FingerTipPosition::FingerTipPosition(Leap::Controller &controller,
                                         Leap::Finger::Type type)
            : _controller(controller), _type(type), _hasChanged(false) {}

    void FingerTipPosition::update() {
        auto frame = _controller.frame();
        for (auto &&finger : frame.fingers()) {
            if (_type == finger.type()) {
                _hasChanged = (_position != finger.tipPosition());
                _position = finger.tipPosition();
            }
        }
    }

    bool FingerTipPosition::hasChanged() { return _hasChanged; }

    const Leap::Vector &FingerTipPosition::position() { return _position; }

}}
