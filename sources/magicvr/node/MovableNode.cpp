#include "magicvr/node/MovableNode.hpp"

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGSimpleGeometry.h>

namespace magicvr { namespace node {
    using namespace OSG;

    NodeTransitPtr MovableNode::node(const NodeRecPtr child) {
        if (_node == nullptr) {
            _transformer = ComponentTransformBase::create();
            _node = makeNodeFor(_transformer);
            _node->addChild(child);
        } else {
            _node->clearChildren();
            _node->addChild(child);
        }
        return NodeTransitPtr(_node);
    }

    NodeTransitPtr MovableNode::node() {
        if (_node == nullptr) {
            _transformer = ComponentTransformBase::create();
            _node = makeNodeFor(_transformer);
            _node->addChild(defaultChild());
        }
        return NodeTransitPtr(_node);
    }

    NodeTransitPtr MovableNode::defaultChild() {
        return makeBox(10, 10, 10, true, true, true);
    }

    void MovableNode::moveTo(const Vec3f &newPosition) {
        _transformer->setTranslation(newPosition);
    }

}}