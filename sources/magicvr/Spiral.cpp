#include "magicvr/Spiral.hpp"

std::vector<OSG::Vec3f> Spiral::sample() const {
    std::vector<OSG::Vec3f> sampled;
    const int step = 10;
    float radius = 0;
    int angle = 0;
    int angleCounter = 0;
    while (angleCounter <= 517.5) {
        float x = std::cos(OSG::osgDegree2Rad((float) angle)) * radius;
        float y = -std::sin(OSG::osgDegree2Rad((float) angle)) * radius;
        sampled.push_back({x, y, 0});

        angle = (angle - step) % 360;
        angleCounter += step;
        const float radiusStep = (angleCounter < 45 ? 2 : angleCounter < 90 ? 1 : angleCounter < 270 ? 0.1f : 0.7f);
        radius += radiusStep;
    }
    return sampled;
}
