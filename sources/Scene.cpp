#include <cstdlib>
#include <iostream>

#include <OSGCSM/OSGCAVESceneManager.h>

#include "Scene.hpp"


void Scene::build() {
    root->setCore(Group::create());

    NodeRecPtr cylinderTrans = makeNodeFor(cylinderCT);
    cylinderTrans->addChild(makeCylinder(25, 1, 16, true, true, true));

    switchBox->setChoice(0);
    NodeRecPtr switchBoxNode = makeNodeFor(switchBox);
    switchBoxNode->addChild(makeBox(5, 4, 4, 1, 1, 1));

    torusCT->setTranslation(wand.position);
    NodeRecPtr torusTrans = makeNodeFor(torusCT);
    torusTrans->addChild(makeTorus(10.f, 50.f, 32, 64));

    root->addChild(cylinderTrans);
    root->addChild(switchBoxNode);
    root->addChild(torusTrans);
}

void Scene::update() {
    torusCT->setTranslation(wand.position);
    torusCT->setRotation(wand.orientation);

    cylinderCT->setTranslation(wand.position);
    cylinderCT->setRotation(wand.orientation * Quaternion(Vec3f(1, 0, 0), osgDegree2Rad(90)));
}

void Scene::showBox(bool isVisible) {
    switchBox->setChoice(isVisible);
}