#ifndef MAGICVR_ANIMATION_HPP
#define MAGICVR_ANIMATION_HPP

class Animation {
    bool _stopped = false;

public:
    virtual void animate(float dTime)= 0;

    void stop();

    bool isStopped() const;
};


#endif //MAGICVR_ANIMATION_HPP
