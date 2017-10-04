#ifndef MAGICVR_APPCONTROLLER_HPP
#define MAGICVR_APPCONTROLLER_HPP


#include <Scene.hpp>
#include "AppModel.hpp"
#include "MagicTricks.hpp"

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

protected:
    magicvr::MagicTricks _tricks;

public:
    AppController();

    virtual void display(OSG::Time dTime);

    virtual void keyboardDown(unsigned char key, int x, int y);

    virtual void keyboardUp(unsigned char key, int x, int y);

    const NodeRecPtr &root() const;

    Scene &scene();
};


#endif //MAGICVR_APPCONTROLLER_HPP
