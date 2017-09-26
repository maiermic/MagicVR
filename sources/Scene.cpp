#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>

void Scene::build() {
    root()->addChild(buildRealWorldScale());
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
            .node();
}

const NodeTransitPtr Scene::buildFrontRightPedestal() const {
    return ComponentTransformNode()
            .translate(1, 0, -1)
            .rotate(Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(0)))
            .scale(0.5, 1, 0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Sockel.obj"))
            .addChild(buildFireElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildFireElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(2, 1, 2)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(-30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Fire.obj"))
            .addChild(buildFireElement())
            .node();
}

const NodeTransitPtr Scene::buildFireElement() const {
    return ComponentTransformNode(fireUnlockedCT)
            .rotate(Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(-90)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/FireUnlocked.obj"))
            .node();
}

const NodeTransitPtr Scene::buildFrontLeftPedestal() const {
    return ComponentTransformNode()
            .translate(-1, 0, -1)
            .rotate(Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(0)))
            .scale(0.5, 1, 0.5)
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Sockel.obj"))
            .addChild(buildWaterElementalStone())
            .node();
}

const NodeTransitPtr Scene::buildWaterElementalStone() const {
    return ComponentTransformNode()
            .translate(0, 1, 0)
            .scale(2, 1, 2)
            .rotate(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Water.obj"))
            .addChild(buildWaterElement())
            .node();
}

const NodeTransitPtr Scene::buildWaterElement() const {
    return ComponentTransformNode(waterUnlockedCT)
            .rotate(Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(-90)))
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/WaterUnlocked.obj"))
            .node();
}

void Scene::update(float dTime) {
    _animations.animate(dTime);
}

Scene::Scene() : _root(makeNodeFor(Group::create())),
                 fireUnlockedCT(ComponentTransformBase::create()),
                 waterUnlockedCT(ComponentTransformBase::create()) {
    build();
    update(0);
}

const NodeRecPtr &Scene::root() const {
    return _root;
}

void Scene::unlockFire() {
    const auto trans = fireUnlockedCT->getTranslation();
    _animations.add(
            std::shared_ptr<Animation>(
                    new TranslationAnimation(
                            fireUnlockedCT,
                            OSG::Vec3f(trans.x(), trans.y() + 0.5f, trans.z()),
                            2)));
}

void Scene::unlockWater() {
    const auto trans = waterUnlockedCT->getTranslation();
    _animations.add(
            std::shared_ptr<Animation>(
                    new TranslationAnimation(
                            waterUnlockedCT,
                            OSG::Vec3f(trans.x(), trans.y() + 0.5f, trans.z()),
                            2)));
}
