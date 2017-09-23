#include "Scene.hpp"
#include <OpenSG/OSGSceneFileHandler.h>

void Scene::build() {
    /*realWorldScale
     *
     * Modelle, die mit Blender erstellt wurden werden vom
     * OSGFileHandler um den Faktor 100 zu klein interpretiert.
     *
     * -> Die gesamt Szene auf 100 hochskalieren
     *
     * => künftig Translation 1 = 1m
     * => künftig Scale 1 = 100% */
    const ComponentTransformRecPtr realWorldScaleCT = ComponentTransformBase::create();
    realWorldScaleCT->setTranslation(Vec3f(0, 0, 0));
    realWorldScaleCT->setRotation(Quaternion(Vec3f(0, 0, 0), osgDegree2Rad(0)));
    realWorldScaleCT->setScale(Vec3f(100, 100, 100));
    const NodeRecPtr realWorldScaleTrans = makeNodeFor(realWorldScaleCT);



    /*WaterUnlocked*/
    const NodeRecPtr waterUnlocked = SceneFileHandler::the()->read("models/WaterUnlocked.obj");
    waterUnlockedCT->setTranslation(Vec3f(0, 0, 0));
    waterUnlockedCT->setRotation(Quaternion(Vec3f(1,0,0),osgDegree2Rad(-90)));
    waterUnlockedCT->setScale(Vec3f(1, 1, 1));
    const NodeRecPtr waterUnlockedTrans = makeNodeFor(waterUnlockedCT);
    waterUnlockedTrans->addChild(waterUnlocked);



    /*Water*/
    const NodeRecPtr water = SceneFileHandler::the()->read("models/Water.obj");
    const ComponentTransformRecPtr waterCT = ComponentTransformBase::create();
    waterCT->setTranslation(Vec3f(0, 1, 0));
    waterCT->setScale(Vec3f(2, 1, 2));
    waterCT->setRotation(Quaternion(Vec3f(0, 1, 0), osgDegree2Rad(30)));
    const NodeRecPtr waterTrans = makeNodeFor(waterCT);
    waterTrans->addChild(water);



    /*SockelVorneLinks*/
    const NodeRecPtr sockelVorneLinks = SceneFileHandler::the()->read("models/Sockel.obj");

    const ComponentTransformRecPtr sockelVorneLinksCT = ComponentTransformBase::create();

    sockelVorneLinksCT->setTranslation(Vec3f(-1, 0, -1));
    sockelVorneLinksCT->setRotation(Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(0)));
    sockelVorneLinksCT->setScale(Vec3f(0.5, 1, 0.5));

    const NodeRecPtr sockelVorneLinksTrans = makeNodeFor(sockelVorneLinksCT);
    sockelVorneLinksTrans->addChild(sockelVorneLinks);



    /*Compose
     *
     * Beginne mit untersten Objekten zurück bis root*/
    waterTrans->addChild(waterUnlockedTrans);
    // TODO add other elements

    sockelVorneLinksTrans->addChild(waterTrans);
    // TODO add children to other sockels

    realWorldScaleTrans->addChild(sockelVorneLinksTrans);
    // TODO add other sockels

    root()->addChild(realWorldScaleTrans);
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
