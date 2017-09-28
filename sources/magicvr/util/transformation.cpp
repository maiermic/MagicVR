#include "magicvr/util/transformation.hpp"

#include <OpenSG/OSGComponentTransform.h>

namespace magicvr { namespace util {
    using namespace OSG;

    NodeTransitPtr
    translateNode(const NodeRecPtr node, const Vec3f translation) {
        auto transform = ComponentTransformBase::create();
        transform->setTranslation(translation);
        auto transformNode = makeNodeFor(transform);
        transformNode->addChild(node);
        return transformNode;
    }
}}
