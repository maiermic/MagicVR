#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <magicvr/ComponentTransformNode.hpp>
#include <magicvr/animation/TranslationAnimation.hpp>
#include "magicvr/animation/ScaleAnimation.hpp"
#include "magicvr/animation/SequentialAnimation.hpp"

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
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Earth.obj"))
            .addChild(buildEarthElement())
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
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Fire.obj"))
            .addChild(buildFireElement())
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
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Water.obj"))
            .addChild(buildWaterElement())
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
            .addChild(SingletonHolder<SceneFileHandlerBase>::the()->read("models/Thunder.obj"))
            .addChild(buildThunderElement())
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

Scene::Scene() : _root(makeNodeFor(Group::create())),
                 earthUnlockedCT(ComponentTransformBase::create()),
                 fireUnlockedCT(ComponentTransformBase::create()),
                 waterUnlockedCT(ComponentTransformBase::create()),
                 thunderUnlockedCT(ComponentTransformBase::create()) {
    build();
    update(0);
}

const NodeRecPtr &Scene::root() const {
    return _root;
}

void Scene::unlockElement(const ComponentTransformRecPtr elementCT) {
    const auto trans = elementCT->getTranslation();
    _animations.add(
            std::shared_ptr<Animation>(
                    new SequentialAnimation{
                            std::shared_ptr<Animation>(
                                    new TranslationAnimation(
                                            elementCT,
                                            OSG::Vec3f(trans.x(),
                                                       trans.y() + 0.5f,
                                                       trans.z()),
                                            2)),
                            std::shared_ptr<Animation>(
                                    new ScaleAnimation(
                                            elementCT,
                                            OSG::Vec3f(2, 2, 2),
                                            2))
                    })
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
