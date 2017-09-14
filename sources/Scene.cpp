#include <cstdlib>
#include <iostream>

#include <OpenSG/OSGSimpleGeometry.h>
#include <OpenSG/OSGSwitch.h>

#include <OSGCSM/OSGCAVESceneManager.h>

#include "Scene.h"


void Scene::build() {
    NodeRecPtr root = Node::create();
    root->setCore(Group::create());

    NodeRecPtr cylinder = makeCylinder(25, 1, 16, true, true, true);
    cylinderCT = ComponentTransform::create();
    NodeRecPtr cylinderTrans = makeNodeFor(cylinderCT);
    cylinderTrans->addChild(cylinder);

    NodeRecPtr box = makeBox(5, 4, 4, 1, 1, 1);
    switchBox = Switch::create();
    switchBox->setChoice(0);
    NodeRecPtr switchBoxNode = Node::create();
    switchBoxNode->setCore(switchBox);
    switchBoxNode->addChild(box);

    auto torus = makeTorus(10.f, 50.f, 32.f, 64.f);
    torusCT = ComponentTransform::create();
    torusCT->setTranslation(wand.position);
    NodeRecPtr torusTrans = makeNodeFor(torusCT);
    torusTrans->addChild(torus);

    root->addChild(cylinderTrans);
    root->addChild(switchBoxNode);
    root->addChild(torusTrans);

    this->root = NodeTransitPtr(root);
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