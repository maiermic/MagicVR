#include <OpenSG/OSGSimpleGeometry.h>

#include "magicvr/node/node.hpp"

namespace magicvr { namespace node {
    using namespace OSG;

    NodeTransitPtr
    pointNode(const Vec3f &pos,
              const Real32 size,
              const MaterialRecPtr material) {
        auto transform = ComponentTransformBase::create();
        transform->setTranslation(pos);
        auto node = makeNodeFor(transform);
        auto geo = makeSphereGeo(2, size);
        geo->setMaterial(material);
        node->addChild(makeNodeFor(geo));
        return node;
    }

    NodeTransitPtr
    lineNode(const Vec3f &start,
             const Vec3f &end,
             const Real32 size,
             const MaterialRecPtr material) {
        auto transform = ComponentTransformBase::create();
        const Vec3f d(end - start);
        const Vec3f d2(d.x(), -d.y(), d.z());
        const Vec3f cylinder_direction(0, 1, 0);
        const Vec3f normal(d2.cross(cylinder_direction));
        const auto angle = d2.enclosedAngle(cylinder_direction);
        transform->setRotation(Quaternion(normal, angle));
        transform->setTranslation(start + (d / 2));
        auto node_transform = makeNodeFor(transform);
        auto geo = makeCylinderGeo(d.length(), size, 32, true, true, true);
        geo->setMaterial(material);
        node_transform->addChild(makeNodeFor(geo));
        return node_transform;
    }

    NodeTransitPtr
    segmentNode(const Vec3f &start,
                const Vec3f &end,
                const Real32 size,
                const MaterialRecPtr material) {
        auto group = makeNodeFor(Group::create());
        group->addChild(pointNode(start, size, material));
        group->addChild(lineNode(start, end, size, material));
        group->addChild(pointNode(end, size, material));
        return group;
    }
}}
