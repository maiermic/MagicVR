#pragma once

#include <magicvr/ComponentTransformNode.hpp>
#include <OpenSG/OSGSwitch.h>
#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <OpenSG/OSGSimpleTexturedMaterialBase.h>
#include <PathSettings.hpp>
#include <OpenSG/OSGSceneFileHandler.h>

namespace magicvr { namespace node {

    enum WandBulb : int {
        NO_BULB = OSG::Switch::NONE,
        DEFAULT_BULB = 0,
        FIRE_BULB,
        WATER_BULB,
        THUNDER_BULB,
    };

    class WandNode {
        ComponentTransformNode _root;
        OSG::SwitchRecPtr _switch;

    public:
        WandNode();

        OSG::NodeTransitPtr buildBubble(const OSG::Char8 * modelPath) const;

        OSG::NodeTransitPtr buildDefault() const;

        void showBulb(WandBulb bulb);

        ComponentTransformNode node() const;
    };

}}

