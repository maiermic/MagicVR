#ifndef MAGICVR_APPCONTROLLER_HPP
#define MAGICVR_APPCONTROLLER_HPP


#include <Scene.hpp>
#include "AppModel.hpp"

/**
 * Controller of the app logic, model and view (-model).
 * The model is used in the app logic.
 * The view contains the scene graph that is displayed.
 */
class AppController {
    /**
     * Data used in the app logic.
     */
    AppModel _model;

    /**
     * The view (-model) that contains the scene graph that is displayed.
     */
    Scene _scene;

public:
    void display(OSG::Time dTime);

    void keyboardDown(unsigned char key, int x, int y);

    const NodeRecPtr &root() const;
};


#endif //MAGICVR_APPCONTROLLER_HPP
