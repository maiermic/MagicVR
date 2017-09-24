#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>
#include <magicvr/ComponentTransformNode.hpp>

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

void Scene::update() {
}

Scene::Scene() : _root(makeNodeFor(Group::create())), waterUnlockedCT(ComponentTransformBase::create()) {
    build();
    update();
}

const NodeRecPtr &Scene::root() const {
    return _root;
}
