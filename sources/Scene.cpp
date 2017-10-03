#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include <magicvr/animation/BezierCurve.hpp>
#include <magicvr/node/TrajectoryContainerNode.hpp>
#include <magicvr/animation/BezierAnimation.hpp>
#include <magicvr/animation/EaseInOutAnimation.hpp>
#include "magicvr/animation/ScaleAnimation.hpp"
#include "magicvr/animation/SequentialAnimation.hpp"

void Scene::build() {
    root()->addChild(buildRealWorldScale());
//    root()->addChild(buildBezierCurve());
//    root()->addChild(buildTest());
}

const NodeRecPtr Scene::buildTest() const {
    return ComponentTransformNode()
            .scale(100, 100, 100)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Stonehenge.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubbles() const {
    return ComponentTransformNode()
            .translate(0, 0.25, 0)
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
            .translate(0, 0.25, 0)
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
            .translate(0, 0.25, 0)
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
            .translate(0, 0.25, 0)
            .scale(1)
            .addChild(buildEarthBubble1())
            .addChild(buildEarthBubble2())
            .addChild(buildEarthBubble3())
            .addChild(buildEarthBubble4())
            .addChild(buildEarthBubble5())
            .addChild(buildEarthBubble6())
            .addChild(buildEarthBubble7())
            .addChild(buildEarthBubble8())
            .node();
}

const NodeTransitPtr Scene::buildFireBubble1() const {
    return ComponentTransformNode(fireBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble2() const {
    return ComponentTransformNode(fireBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble3() const {
    return ComponentTransformNode(fireBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble4() const {
    return ComponentTransformNode(fireBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble5() const {
    return ComponentTransformNode(fireBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble6() const {
    return ComponentTransformNode(fireBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble7() const {
    return ComponentTransformNode(fireBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFireBubble8() const {
    return ComponentTransformNode(fireBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Fire.obj"))
            .node();
}


const NodeTransitPtr Scene::buildWaterBubble1() const {
    return ComponentTransformNode(waterBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble2() const {
    return ComponentTransformNode(waterBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble3() const {
    return ComponentTransformNode(waterBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble4() const {
    return ComponentTransformNode(waterBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble5() const {
    return ComponentTransformNode(waterBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble6() const {
    return ComponentTransformNode(waterBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble7() const {
    return ComponentTransformNode(waterBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}

const NodeTransitPtr Scene::buildWaterBubble8() const {
    return ComponentTransformNode(waterBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Water.obj"))
            .node();
}


const NodeTransitPtr Scene::buildThunderBubble1() const {
    return ComponentTransformNode(thunderBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble2() const {
    return ComponentTransformNode(thunderBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble3() const {
    return ComponentTransformNode(thunderBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble4() const {
    return ComponentTransformNode(thunderBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble5() const {
    return ComponentTransformNode(thunderBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble6() const {
    return ComponentTransformNode(thunderBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble7() const {
    return ComponentTransformNode(thunderBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}

const NodeTransitPtr Scene::buildThunderBubble8() const {
    return ComponentTransformNode(thunderBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Thunder.obj"))
            .node();
}


const NodeTransitPtr Scene::buildEarthBubble1() const {
    return ComponentTransformNode(earthBubbleCT1)
            .translate(0, 0, 0)
            .scale(1)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble2() const {
    return ComponentTransformNode(earthBubbleCT2)
            .translate(0, 0, 0)
            .scale(0.9)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble3() const {
    return ComponentTransformNode(earthBubbleCT3)
            .translate(0, 0, 0)
            .scale(0.8)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble4() const {
    return ComponentTransformNode(earthBubbleCT4)
            .translate(0, 0, 0)
            .scale(0.7)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble5() const {
    return ComponentTransformNode(earthBubbleCT5)
            .translate(0, 0, 0)
            .scale(0.6)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble6() const {
    return ComponentTransformNode(earthBubbleCT6)
            .translate(0, 0, 0)
            .scale(0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble7() const {
    return ComponentTransformNode(earthBubbleCT7)
            .translate(0, 0, 0)
            .scale(0.4)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
            .node();
}

const NodeTransitPtr Scene::buildEarthBubble8() const {
    return ComponentTransformNode(earthBubbleCT8)
            .translate(0, 0, 0)
            .scale(0.3)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Bubbles_Earth.obj"))
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

void Scene::animateEarthBubbles() {
    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT1,
                                    Vec3f(0, 1, 0),
                                    3 * 1, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT1,
                                    Vec3f(0, 0, 0),
                                    3 * 1, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT2,
                                    Vec3f(0, 1, 0),
                                    3 * 0.9, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT2,
                                    Vec3f(0, 0, 0),
                                    3 * 0.9, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT3,
                                    Vec3f(0, 1, 0),
                                    3 * 0.8, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT3,
                                    Vec3f(0, 0, 0),
                                    3 * 0.8, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT4,
                                    Vec3f(0, 1, 0),
                                    3 * 0.7, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT4,
                                    Vec3f(0, 0, 0),
                                    3 * 0.7, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT5,
                                    Vec3f(0, 1, 0),
                                    3 * 0.6, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT5,
                                    Vec3f(0, 0, 0),
                                    3 * 0.6, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT6,
                                    Vec3f(0, 1, 0),
                                    3 * 0.5, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT6,
                                    Vec3f(0, 0, 0),
                                    3 * 0.5, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT7,
                                    Vec3f(0, 1, 0),
                                    3 * 0.4, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT7,
                                    Vec3f(0, 0, 0),
                                    3 * 0.4, true))
            }
    ));

    _animations.add(std::shared_ptr<Animation>(
            new ParallelAnimation{
                    std::shared_ptr<Animation>(
                            new TranslationAnimation(
                                    earthBubbleCT8,
                                    Vec3f(0, 1, 0),
                                    3 * 0.3, true)),

                    std::shared_ptr<Animation>(
                            new ScaleAnimation(
                                    earthBubbleCT8,
                                    Vec3f(0, 0, 0),
                                    3 * 0.3, true))
            }
    ));
}

const NodeRecPtr Scene::buildRealWorldScale() const {
    /*realWorldScale
     *
     * Modelle, die mit Blender erstellt wurden werden vom
     * OSGFileHandler um den Faktor 100 zu klein interpretiert.
     *
     * -> Die gesamt Szene auf 100 hochskalieren
     *
     * => künftig Translation 1 = 1m
     * => künftig Scale 1 = 100% */
    return ComponentTransformNode()
            .scale(100)
            .addChild(buildFrontLeftPedestal())
            .addChild(buildFrontRightPedestal())
            .addChild(buildBackLeftPedestal())
            .addChild(buildBackRightPedestal())
            .node();
}

const NodeTransitPtr Scene::buildBackLeftPedestal() const {
    return buildPedestal()
            .translate(-1, 0, 1)
            .addChild(buildEarthElementalStone())
            .node();
}

ComponentTransformNode Scene::buildPedestal() const {
    return ComponentTransformNode()
            .scale(0.5, 1, 0.5)
            .addChild(
                    SingletonHolder<SceneFileHandlerBase>::the()
                            ->read("models/Sockel.obj"));
}

const NodeTransitPtr Scene::buildEarthElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(2, 1, 2)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Earth.obj"))
            .addChild(buildEarthBubbles())
            .node();
}

const NodeTransitPtr Scene::buildEarthElement() const {
    return buildElement(earthUnlockedCT, "models/EarthUnlocked.obj");
}

const NodeTransitPtr Scene::buildFrontRightPedestal() const {
    return buildPedestal()
            .translate(1, 0, -1)
            .addChild(buildFireElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildFireElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(2, 1, 2)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(-30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Fire.obj"))
            .addChild(buildFireBubbles())
            .node();
}

const NodeTransitPtr Scene::buildFireElement() const {
    return buildElement(fireUnlockedCT, "models/FireUnlocked.obj");
}

const NodeTransitPtr Scene::buildFrontLeftPedestal() const {
    return buildPedestal()
            .translate(-1, 0, -1)
            .addChild(buildWaterElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildWaterElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(2, 1, 2)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Water.obj"))
            .addChild(buildWaterBubbles())
            .node();
}

const NodeTransitPtr Scene::buildWaterElement() const {
    return buildElement(waterUnlockedCT, "models/WaterUnlocked.obj");
}

const NodeTransitPtr Scene::buildBackRightPedestal() const {
    return buildPedestal()
            .translate(1, 0, 1)
            .addChild(buildThunderElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildThunderElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(2, 1, 2)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(-30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(
                    "models/Thunder.obj"))
            .addChild(buildThunderBubbles())
            .node();
}

const NodeTransitPtr Scene::buildThunderElement() const {
    return buildElement(thunderUnlockedCT, "models/ThunderUnlocked.obj");
}

const NodeTransitPtr Scene::buildElement(const ComponentTransformRecPtr trans,
                                         const char *modelName) const {
    return ComponentTransformNode(trans)
            .rotate(Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(-90)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read(modelName))
            .node();
}

void Scene::update(OSG::Time dTime) {
    _animations.animate(dTime);
}

Scene::Scene() : _animations(ParallelAnimation::DO_NOT_STOP_IF_NO_ANIMATIONS),
                 _root(makeNodeFor(Group::create())),
                 earthUnlockedCT(ComponentTransformBase::create()),
                 fireUnlockedCT(ComponentTransformBase::create()),
                 waterUnlockedCT(ComponentTransformBase::create()),
                 thunderUnlockedCT(ComponentTransformBase::create()),
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
                 earthBubbleCT1(ComponentTransformBase::create()),
                 earthBubbleCT2(ComponentTransformBase::create()),
                 earthBubbleCT3(ComponentTransformBase::create()),
                 earthBubbleCT4(ComponentTransformBase::create()),
                 earthBubbleCT5(ComponentTransformBase::create()),
                 earthBubbleCT6(ComponentTransformBase::create()),
                 earthBubbleCT7(ComponentTransformBase::create()),
                 earthBubbleCT8(ComponentTransformBase::create()) {
    build();
    update(0);
}

const NodeRecPtr &Scene::root() const {
    return _root;
}

void Scene::unlockElement(const ComponentTransformRecPtr elementCT) {
    const auto trans = elementCT->getTranslation();
    const OSG::Time animationDuration = 2;
    _animations.add(
            std::shared_ptr<Animation>(
                    new EaseInOutAnimation(
                            animationDuration,
                            std::shared_ptr<Animation>(
                                    new SequentialAnimation{
                                            std::shared_ptr<Animation>(
                                                    new TranslationAnimation(
                                                            elementCT,
                                                            OSG::Vec3f(
                                                                    trans.x(),
                                                                    trans.y() +
                                                                    0.5f,
                                                                    trans.z()),
                                                            animationDuration, false)),
                                            std::shared_ptr<Animation>(
                                                    new ScaleAnimation(
                                                            elementCT,
                                                            OSG::Vec3f(2, 2, 2),
                                                            animationDuration, false))
                                    }
                            ))
            )
    );
}

void Scene::unlockEarth() {
    unlockElement(earthUnlockedCT);
}

void Scene::unlockFire() {
    unlockElement(fireUnlockedCT);
}

void Scene::unlockWater() {
    unlockElement(waterUnlockedCT);
}

void Scene::unlockThunder() {
    unlockElement(thunderUnlockedCT);
}

NodeTransitPtr Scene::buildBezierCurve() const {
    BezierCurve<OSG::Vec2f> bezier2{
            OSG::Vec2f(0, 0),
            OSG::Vec2f(0.75, 0),
            OSG::Vec2f(0.25, 1),
            OSG::Vec2f(1, 1)
    };
    BezierCurve<> bezier{
            OSG::Vec3f(0, 0, 0),
            OSG::Vec3f(75, 0, 0),
            OSG::Vec3f(25, 100, 0),
            OSG::Vec3f(100, 100, 0)
    };
    magicvr::node::TrajectoryContainerNode bezierNode;
    const float numOfSegments = 21;
    for (float i = 0; i < numOfSegments; ++i) {
        bezierNode.add(bezier.atPercentage(i / numOfSegments));
        std::cout << "(" << bezier2.atPercentage(i / numOfSegments) << ")\n";
    }
    return bezierNode.node();
}
