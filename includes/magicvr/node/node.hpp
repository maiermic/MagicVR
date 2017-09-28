#ifndef MAGICVR_NODE_NODE_HPP
#define MAGICVR_NODE_NODE_HPP

#include <iterator>

#include <OpenSG/OSGBaseTypes.h>
#include <OpenSG/OSGComponentTransform.h>
#include <OpenSG/OSGGroup.h>
#include <OpenSG/OSGNode.h>
#include <OpenSG/OSGMaterial.h>
#include <magicvr/util/color.hpp>


namespace magicvr { namespace node {
    OSG::NodeTransitPtr
    pointNode(const OSG::Vec3f &pos,
              const OSG::Real32 size = 1,
              const OSG::MaterialRecPtr material = magicvr::util::defaultMaterialColor());

    OSG::NodeTransitPtr
    lineNode(const OSG::Vec3f &start,
             const OSG::Vec3f &end,
             const OSG::Real32 size = 1,
             const OSG::MaterialRecPtr material = magicvr::util::defaultMaterialColor());

    OSG::NodeTransitPtr
    segmentNode(const OSG::Vec3f &start,
                const OSG::Vec3f &end,
                const OSG::Real32 size = 1,
                const OSG::MaterialRecPtr material = magicvr::util::defaultMaterialColor());
}}

#endif //MAGICVR_NODE_NODE_HPP
