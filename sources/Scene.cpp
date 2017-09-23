#include "Scene.hpp"


void Scene::build() {
}

void Scene::update() {
}

Scene::Scene() : _root(makeNodeFor(Group::create())) {
    build();
    update();
}

const NodeRecPtr &Scene::root() const {
    return _root;
}
