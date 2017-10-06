#ifndef MAGICVR_ANIMATION_HPP
#define MAGICVR_ANIMATION_HPP

#include <OpenSG/OSGTime.h>

class Animation {
    bool _stopped = false;

public:
    virtual void animate(OSG::Time dTime)= 0;

    virtual void stop();

    bool isStopped() const;
};


#endif //MAGICVR_ANIMATION_HPP
