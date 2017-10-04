#ifndef MAGICVR_SPIRAL_HPP
#define MAGICVR_SPIRAL_HPP

#include <vector>
#include <OpenSG/OSGVector.h>


class Spiral {
public:
    std::vector<OSG::Vec3f> sample() const;
};


#endif //MAGICVR_SPIRAL_HPP
