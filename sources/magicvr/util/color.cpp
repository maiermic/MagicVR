#include "magicvr/util/color.hpp"

namespace magicvr { namespace util {
    using namespace OSG;

    SimpleMaterialTransitPtr
    materialColor(const Real32 red,
                  const Real32 green,
                  const Real32 blue,
                  const Real32 transparency) {
        auto material = SimpleMaterialBase::create();
        material->setDiffuse(Color3f(red, green, blue));
        material->setAmbient(Color3f(red, green, blue));
        material->setTransparency(transparency);
        return material;
    }

    SimpleMaterialTransitPtr
    defaultMaterialColor() {
        return materialColor(0.5, 0.5, 0.5);
    }
}}
