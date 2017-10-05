#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <OpenSG/OSGQuaternion.h>
#include <OpenSG/OSGMaterialGroup.h>
#include <OpenSG/OSGImage.h>
#include <OpenSG/OSGSimpleTexturedMaterial.h>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <magicvr/animation/BezierAnimation.hpp>
#include <magicvr/animation/EaseInOutAnimation.hpp>
#include <magicvr/Spiral.hpp>
#include <range/v3/to_container.hpp>
#include <magicvr/ranges/view/Circle.hpp>
#include <magicvr/ranges/view/rotate.hpp>
#include "magicvr/animation/ScaleAnimation.hpp"
#include "magicvr/animation/SequentialAnimation.hpp"
#include "PathSettings.hpp"

void Scene::build() {
    root()->addChild(buildRealWorldScale());
//    root()->addChild(buildBezierCurve());
//    root()->addChild(buildSpiral());

    ComponentTransformNode trajectoryNodes;
    trajectoryNodes.translate(0, 200, -100);

    const SimpleMaterialRecPtr red_material = OSG::SimpleMaterialBase::create();
    red_material->setDiffuse(Color3f(1,0.4f,0));
    red_material->setAmbient(Color3f(0.8f, 0.2f, 0.2f));
    const MaterialGroupRecPtr red_material_group = MaterialGroupBase::create();
    red_material_group->setMaterial(red_material);
    const NodeTransitPtr pattern_trajectory_node_with_material = makeNodeFor(red_material_group);
    pattern_trajectory_node_with_material->addChild(_patternTrajectoryNode.node());
    trajectoryNodes.addChild(pattern_trajectory_node_with_material);

    const SimpleMaterialRecPtr green_material = OSG::SimpleMaterialBase::create();
    green_material->setDiffuse(Color3f(0,1, 0.8f));
    green_material->setAmbient(Color3f(0.2f, 0.8f, 0.2f));
    const MaterialGroupRecPtr green_material_group = MaterialGroupBase::create();
    green_material_group->setMaterial(green_material);
    const NodeTransitPtr input_trajectory_node_with_material = makeNodeFor(green_material_group);
    input_trajectory_node_with_material->addChild(_inputTrajectoryNode.node());
    trajectoryNodes.addChild(input_trajectory_node_with_material);

    trajectoryNodes.addChild(_preprocessedInputTrajectoryNode.node());
//    root()->addChild(_inputTrajectoryNode.node());
//    root()->addChild(_patternTrajectoryNode.node());
    root()->addChild(trajectoryNodes.node());

    auto c =
            magicvr::ranges::view::Circle(100).sample(0, 360, 10) |
            ranges::view::transform([](OSG::Vec2f v) {
                return OSG::Vec3f(v.x(), v.y(), 0);
            }) |
            magicvr::ranges::view::rotate(
                    OSG::Quaternion(
                            OSG::Vec3f(0.f, 1.f, 0.f),
                            OSG::osgDegree2Rad(90)
                    )
            ) |
            ranges::to_vector;
//    root()->addChild(
//            magicvr::node::TrajectoryContainerNode(std::move(c)).node()
//    );
}

const NodeTransitPtr Scene::buildStonehenge() const {
    return ComponentTransformNode()
            .translate(-1, 0, -2)
            .translate(-1,0.5,-2)
            .scale(0.02f)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(95)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_Stonehenge))
            .node();
}

const NodeTransitPtr Scene::buildLantern() const {
    return ComponentTransformNode()
            .translate(0,0,0)
            .scale(0.1f)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_Lantern))
            .node();
}

const NodeTransitPtr Scene::buildKapelle() const {
    return ComponentTransformNode()
            /* TODO: Decide for position
             * */
//            .translate(0,-0.17f,1.8)
            .translate(0,-0.35f,5)
            .scale(12)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(90)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_Kapelle))
            .node();
}


const NodeTransitPtr Scene::buildFireBubbles() const {
    return ComponentTransformNode()
            .translate(0, 0.1f, 0)
            .scale(1)
            .addChild(buildFireBubble1())
            .addChild(buildFireBubble2())
            .addChild(buildFireBubble3())
            .addChild(buildFireBubble4())
            .addChild(buildFireBubble5())
            .addChild(buildFireBubble6())
            .addChild(buildFireBubble7())
            .addChild(buildFireBubble8())
            .node();
}

const NodeTransitPtr Scene::buildWaterBubbles() const {
    return ComponentTransformNode()
            .translate(0, 0.1f, 0)
            .scale(1)
            .addChild(buildWaterBubble1())
            .addChild(buildWaterBubble2())
            .addChild(buildWaterBubble3())
            .addChild(buildWaterBubble4())
            .addChild(buildWaterBubble5())
            .addChild(buildWaterBubble6())
            .addChild(buildWaterBubble7())
            .addChild(buildWaterBubble8())
            .node();
}

const NodeTransitPtr Scene::buildThunderBubbles() const {
    return ComponentTransformNode()
            .translate(0, 0.1f, 0)
            .scale(1)
            .addChild(buildThunderBubble1())
            .addChild(buildThunderBubble2())
            .addChild(buildThunderBubble3())
            .addChild(buildThunderBubble4())
            .addChild(buildThunderBubble5())
            .addChild(buildThunderBubble6())
            .addChild(buildThunderBubble7())
            .addChild(buildThunderBubble8())
            .node();
}

const NodeTransitPtr Scene::buildEarthBubbles() const {
    return ComponentTransformNode()
            .translate(0, 0.1f, 0)
            .scale(1)
            .addChild(buildWindBubble1())
            .addChild(buildWindBubble2())
            .addChild(buildWindBubble3())
            .addChild(buildWindBubble4())
            .addChild(buildWindBubble5())
            .addChild(buildWindBubble6())
            .addChild(buildWindBubble7())
            .addChild(buildWindBubble8())
            .node();
}


const NodeTransitPtr Scene::buildFireBubble1() const {
    return ComponentTransformNode(fireBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble2() const {
    return ComponentTransformNode(fireBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble3() const {
    return ComponentTransformNode(fireBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble4() const {
    return ComponentTransformNode(fireBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble5() const {
    return ComponentTransformNode(fireBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble6() const {
    return ComponentTransformNode(fireBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble7() const {
    return ComponentTransformNode(fireBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble8() const {
    return ComponentTransformNode(fireBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireBubble))
            .node();
}


const NodeTransitPtr Scene::buildWaterBubble1() const {
    return ComponentTransformNode(waterBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble2() const {
    return ComponentTransformNode(waterBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble3() const {
    return ComponentTransformNode(waterBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble4() const {
    return ComponentTransformNode(waterBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble5() const {
    return ComponentTransformNode(waterBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble6() const {
    return ComponentTransformNode(waterBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble7() const {
    return ComponentTransformNode(waterBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble8() const {
    return ComponentTransformNode(waterBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterBubble))
            .node();
}


const NodeTransitPtr Scene::buildThunderBubble1() const {
    return ComponentTransformNode(thunderBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble2() const {
    return ComponentTransformNode(thunderBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble3() const {
    return ComponentTransformNode(thunderBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble4() const {
    return ComponentTransformNode(thunderBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble5() const {
    return ComponentTransformNode(thunderBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble6() const {
    return ComponentTransformNode(thunderBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble7() const {
    return ComponentTransformNode(thunderBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble8() const {
    return ComponentTransformNode(thunderBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderBubble))
            .node();
}


const NodeTransitPtr Scene::buildWindBubble1() const {
    return ComponentTransformNode(windBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble2() const {
    return ComponentTransformNode(windBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble3() const {
    return ComponentTransformNode(windBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble4() const {
    return ComponentTransformNode(windBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble5() const {
    return ComponentTransformNode(windBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble6() const {
    return ComponentTransformNode(windBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble7() const {
    return ComponentTransformNode(windBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}

const NodeTransitPtr Scene::buildWindBubble8() const {
    return ComponentTransformNode(windBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindBubble))
            .node();
}


void Scene::animateFireBubbles() {
    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT1,
                                    Vec3f(0, 1, 0),
                                    3 * 1, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT1,
                                    Vec3f(0, 0, 0),
                                    3 * 1, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT2,
                                    Vec3f(0, 1, 0),
                                    3 * 0.9, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT2,
                                    Vec3f(0, 0, 0),
                                    3 * 0.9, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT3,
                                    Vec3f(0, 1, 0),
                                    3 * 0.8, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT3,
                                    Vec3f(0, 0, 0),
                                    3 * 0.8, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT4,
                                    Vec3f(0, 1, 0),
                                    3 * 0.7, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT4,
                                    Vec3f(0, 0, 0),
                                    3 * 0.7, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT5,
                                    Vec3f(0, 1, 0),
                                    3 * 0.6, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT5,
                                    Vec3f(0, 0, 0),
                                    3 * 0.6, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT6,
                                    Vec3f(0, 1, 0),
                                    3 * 0.5, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT6,
                                    Vec3f(0, 0, 0),
                                    3 * 0.5, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT7,
                                    Vec3f(0, 1, 0),
                                    3 * 0.4, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT7,
                                    Vec3f(0, 0, 0),
                                    3 * 0.4, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    fireBubbleCT8,
                                    Vec3f(0, 1, 0),
                                    3 * 0.3, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    fireBubbleCT8,
                                    Vec3f(0, 0, 0),
                                    3 * 0.3, true))
            }
    ));
}

void Scene::animateWaterBubbles() {
    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT1,
                                    Vec3f(0, 1, 0),
                                    3 * 1, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT1,
                                    Vec3f(0, 0, 0),
                                    3 * 1, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT2,
                                    Vec3f(0, 1, 0),
                                    3 * 0.9, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT2,
                                    Vec3f(0, 0, 0),
                                    3 * 0.9, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT3,
                                    Vec3f(0, 1, 0),
                                    3 * 0.8, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT3,
                                    Vec3f(0, 0, 0),
                                    3 * 0.8, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT4,
                                    Vec3f(0, 1, 0),
                                    3 * 0.7, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT4,
                                    Vec3f(0, 0, 0),
                                    3 * 0.7, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT5,
                                    Vec3f(0, 1, 0),
                                    3 * 0.6, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT5,
                                    Vec3f(0, 0, 0),
                                    3 * 0.6, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT6,
                                    Vec3f(0, 1, 0),
                                    3 * 0.5, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT6,
                                    Vec3f(0, 0, 0),
                                    3 * 0.5, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT7,
                                    Vec3f(0, 1, 0),
                                    3 * 0.4, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT7,
                                    Vec3f(0, 0, 0),
                                    3 * 0.4, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    waterBubbleCT8,
                                    Vec3f(0, 1, 0),
                                    3 * 0.3, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    waterBubbleCT8,
                                    Vec3f(0, 0, 0),
                                    3 * 0.3, true))
            }
    ));
}

void Scene::animateThunderBubbles() {
    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT1,
                                    Vec3f(0, 1, 0),
                                    3 * 1, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT1,
                                    Vec3f(0, 0, 0),
                                    3 * 1, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT2,
                                    Vec3f(0, 1, 0),
                                    3 * 0.9, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT2,
                                    Vec3f(0, 0, 0),
                                    3 * 0.9, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT3,
                                    Vec3f(0, 1, 0),
                                    3 * 0.8, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT3,
                                    Vec3f(0, 0, 0),
                                    3 * 0.8, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT4,
                                    Vec3f(0, 1, 0),
                                    3 * 0.7, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT4,
                                    Vec3f(0, 0, 0),
                                    3 * 0.7, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT5,
                                    Vec3f(0, 1, 0),
                                    3 * 0.6, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT5,
                                    Vec3f(0, 0, 0),
                                    3 * 0.6, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT6,
                                    Vec3f(0, 1, 0),
                                    3 * 0.5, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT6,
                                    Vec3f(0, 0, 0),
                                    3 * 0.5, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT7,
                                    Vec3f(0, 1, 0),
                                    3 * 0.4, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT7,
                                    Vec3f(0, 0, 0),
                                    3 * 0.4, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    thunderBubbleCT8,
                                    Vec3f(0, 1, 0),
                                    3 * 0.3, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    thunderBubbleCT8,
                                    Vec3f(0, 0, 0),
                                    3 * 0.3, true))
            }
    ));
}

void Scene::animateWindBubbles() {
    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT1,
                                    Vec3f(0, 1, 0),
                                    3 * 1, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT1,
                                    Vec3f(0, 0, 0),
                                    3 * 1, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT2,
                                    Vec3f(0, 1, 0),
                                    3 * 0.9, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT2,
                                    Vec3f(0, 0, 0),
                                    3 * 0.9, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT3,
                                    Vec3f(0, 1, 0),
                                    3 * 0.8, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT3,
                                    Vec3f(0, 0, 0),
                                    3 * 0.8, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT4,
                                    Vec3f(0, 1, 0),
                                    3 * 0.7, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT4,
                                    Vec3f(0, 0, 0),
                                    3 * 0.7, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT5,
                                    Vec3f(0, 1, 0),
                                    3 * 0.6, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT5,
                                    Vec3f(0, 0, 0),
                                    3 * 0.6, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT6,
                                    Vec3f(0, 1, 0),
                                    3 * 0.5, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT6,
                                    Vec3f(0, 0, 0),
                                    3 * 0.5, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT7,
                                    Vec3f(0, 1, 0),
                                    3 * 0.4, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT7,
                                    Vec3f(0, 0, 0),
                                    3 * 0.4, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    windBubbleCT8,
                                    Vec3f(0, 1, 0),
                                    3 * 0.3, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    windBubbleCT8,
                                    Vec3f(0, 0, 0),
                                    3 * 0.3, true))
            }
    ));
}


const NodeRecPtr Scene::buildRealWorldScale() const {
    /** realWorldScale
     *
     * Models exported from Blender are interpreted to SMALL by the
     * OSGFileHandler about the factor 100.
     *
     * -> Scale the whole scene up by 100
     *
     * => read/write future Translation as 1 = 1meter
     * => read/write future Scale as 1 = 100% */

    /**
     * Since we have a not working Beamer on the right side
     * of the cave, meanwhile turn the complete scene about 30° to the left */
    return ComponentTransformNode()
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .scale(100)
            .addChild(buildStonehenge())
//            .addChild(buildLantern())
//            .addChild(buildKapelle())
            .addChild(buildFrontLeftPedestal())
            .addChild(buildFrontRightPedestal())
            .addChild(buildBackLeftPedestal())
            .addChild(buildBackRightPedestal())
            .node();
}


const NodeTransitPtr Scene::buildPedestal() const {
    return ComponentTransformNode()
            .scale(0.5, 1, 0.5)
            .addChild(
                    SingletonHolder<SceneFileHandlerBase>::the()
                            ->read(Path_Model_Sockel))
            .node();
}


const NodeTransitPtr Scene::buildFrontLeftPedestal() const {
    return ComponentTransformNode()
            .translate(-0.4f, 0, -1)
            .addChild(buildPedestal())
            .addChild(buildWaterElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildFrontRightPedestal() const {
    return ComponentTransformNode()
            .translate(1.25f, 0, -0.75f)
            .addChild(buildPedestal())
            .addChild(buildFireElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildBackLeftPedestal() const {
    return ComponentTransformNode()
            .translate(-1.25f, 0, -0.75f)
            .addChild(buildPedestal())
            .addChild(buildWindElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildBackRightPedestal() const {
    return ComponentTransformNode()
            .translate(0.4f, 0, -1)
            .addChild(buildPedestal())
            .addChild(buildThunderElementalStone())
            .node();
}


const NodeTransitPtr Scene::buildFireElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(1)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(-30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_FireStone))
            .addChild(buildFireBubbles())
            .node();
}

const NodeTransitPtr Scene::buildWaterElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(1)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WaterStone))
            .addChild(buildWaterBubbles())
            .node();
}

const NodeTransitPtr Scene::buildThunderElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(1)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(-30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_ThunderStone))
            .addChild(buildThunderBubbles())
            .node();
}

const NodeTransitPtr Scene::buildWindElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(1)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    Path_Model_WindStone))
            .addChild(buildEarthBubbles())
            .node();
}


void Scene::update(OSG::Time dTime) {
    _animations.animate(dTime);
}

Scene::Scene() : _animations(ParallelAnimation::DO_NOT_STOP_IF_NO_ANIMATIONS),
                 _root(makeNodeFor(Group::create())),
                 fireBubbleCT1(ComponentTransformBase::create()),
                 fireBubbleCT2(ComponentTransformBase::create()),
                 fireBubbleCT3(ComponentTransformBase::create()),
                 fireBubbleCT4(ComponentTransformBase::create()),
                 fireBubbleCT5(ComponentTransformBase::create()),
                 fireBubbleCT6(ComponentTransformBase::create()),
                 fireBubbleCT7(ComponentTransformBase::create()),
                 fireBubbleCT8(ComponentTransformBase::create()),
                 waterBubbleCT1(ComponentTransformBase::create()),
                 waterBubbleCT2(ComponentTransformBase::create()),
                 waterBubbleCT3(ComponentTransformBase::create()),
                 waterBubbleCT4(ComponentTransformBase::create()),
                 waterBubbleCT5(ComponentTransformBase::create()),
                 waterBubbleCT6(ComponentTransformBase::create()),
                 waterBubbleCT7(ComponentTransformBase::create()),
                 waterBubbleCT8(ComponentTransformBase::create()),
                 thunderBubbleCT1(ComponentTransformBase::create()),
                 thunderBubbleCT2(ComponentTransformBase::create()),
                 thunderBubbleCT3(ComponentTransformBase::create()),
                 thunderBubbleCT4(ComponentTransformBase::create()),
                 thunderBubbleCT5(ComponentTransformBase::create()),
                 thunderBubbleCT6(ComponentTransformBase::create()),
                 thunderBubbleCT7(ComponentTransformBase::create()),
                 thunderBubbleCT8(ComponentTransformBase::create()),
                 windBubbleCT1(ComponentTransformBase::create()),
                 windBubbleCT2(ComponentTransformBase::create()),
                 windBubbleCT3(ComponentTransformBase::create()),
                 windBubbleCT4(ComponentTransformBase::create()),
                 windBubbleCT5(ComponentTransformBase::create()),
                 windBubbleCT6(ComponentTransformBase::create()),
                 windBubbleCT7(ComponentTransformBase::create()),
                 windBubbleCT8(ComponentTransformBase::create()) {
    build();
    update(0);
}

const NodeRecPtr &Scene::root() const {
    return _root;
}

//void Scene::unlockElement(const ComponentTransformRecPtr elementCT) {
//    const auto trans = elementCT->getTranslation();
//    const OSG::Time animationDuration = 2;
//    _animations.add(
//            std::shared_ptr<Animation>(
//                    new EaseInOutAnimation(
//                            animationDuration,
//                            std::shared_ptr<Animation>(
//                                    new SequentialAnimation{
//                                            std::shared_ptr<Animation>(
//                                                    new TranslationAnimation(
//                                                            elementCT,
//                                                            OSG::Vec3f(
//                                                                    trans.x(),
//                                                                    trans.y() +
//                                                                    0.5f,
//                                                                    trans.z()),
//                                                            animationDuration, false)),
//                                            std::shared_ptr<Animation>(
//                                                    new ScaleAnimation(
//                                                            elementCT,
//                                                            OSG::Vec3f(2, 2, 2),
//                                                            animationDuration, false))
//                                    }
//                            ))
//            )
//    );
//}

//void Scene::unlockEarth() {
//    unlockElement(earthUnlockedCT);
//}
//
//void Scene::unlockFire() {
//    unlockElement(fireUnlockedCT);
//}
//
//void Scene::unlockWater() {
//    unlockElement(waterUnlockedCT);
//}
//
//void Scene::unlockThunder() {
//    unlockElement(thunderUnlockedCT);
//}

NodeTransitPtr Scene::buildBezierCurve() const {
    const BezierCurve<> bezier{
            {0,   0,   0},
            {75,  0,   0},
            {25,  100, 0},
            {100, 100, 0}
    };
    return magicvr::node::TrajectoryContainerNode(bezier.sample(21)).node();
}

NodeTransitPtr Scene::buildSpiral() const {
    return magicvr::node::TrajectoryContainerNode(Spiral().sample()).node();
}

void Scene::showInputTrajectory(std::vector<OSG::Vec3f> &&trajectory) {
    _inputTrajectoryNode.trajectory() = trajectory;
    _inputTrajectoryNode.update();
}

void Scene::showPreprocessedInputTrajectory(
        std::vector<OSG::Vec3f> &&trajectory) {
    _preprocessedInputTrajectoryNode.trajectory() = trajectory;
    _preprocessedInputTrajectoryNode.update();
}

void Scene::showPatternTrajectory(std::vector<OSG::Vec3f> &&trajectory) {
    _patternTrajectoryNode.trajectory() = trajectory;
    _patternTrajectoryNode.update();
}
