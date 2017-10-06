#include "magicvr/node/WandNode.hpp"

namespace magicvr { namespace node {

    WandNode::WandNode() {
        _switch = OSG::SwitchBase::create();
        const OSG::NodeRecPtr switchNode = OSG::makeNodeFor(_switch);

        switchNode->addChild(buildDefault());
        switchNode->addChild(buildBubble(Path_Model_FireBubble));
        switchNode->addChild(buildBubble(Path_Model_WaterBubble));
        switchNode->addChild(buildBubble(Path_Model_ThunderBubble));

        showBulb(DEFAULT_BULB);
        _root = ComponentTransformNode()
                .addChild(switchNode);
    }

    OSG::NodeTransitPtr WandNode::buildDefault() const {
        OSG::GeometryRecPtr geo = OSG::makeSphereGeo(2, 1);
        OSG::SimpleMaterialRecPtr material = OSG::SimpleMaterialBase::create();
        material->setDiffuse(OSG::Color3f(1, 0.8f, 0));
        material->setAmbient(OSG::Color3f(0.8f, 0.2f, 0.2f));
        geo->setMaterial(material);
        return OSG::makeNodeFor(geo);
    }

    void WandNode::showBulb(WandBulb bulb) {
        _switch->setChoice(bulb);
    }

    ComponentTransformNode WandNode::node() const {
        return _root;
    }

    OSG::NodeTransitPtr WandNode::buildBubble(const OSG::Char8 *modelPath) const {
        return ComponentTransformNode()
                .scale(40.0f)
                .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                        modelPath))
                .node();
    }
}}