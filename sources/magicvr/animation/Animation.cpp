#include "magicvr/animation/Animation.hpp"

void Animation::stop() {
    _stopped = true;
}

bool Animation::isStopped() const {
    return _stopped;
}
