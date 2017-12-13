#ifndef MAGICVR_APPCONTROLLER_HPP
#define MAGICVR_APPCONTROLLER_HPP


#include <Scene.hpp>
#include <magicvr/node/WandNode.hpp>
#include "AppModel.hpp"
#include "MagicTricks.hpp"

namespace magicvr {

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
    node::WandNode _wandNode;
    node::TrajectoryContainerNode _trajectoryNode;
    magicvr::node::WandBulb _selectedWandBulb;
    int _bulbCount;
    OSG::Time _timeSinceStart = 0;
    OSG::Time _nextShotTime = 0;
    bool _isShooting = false;
    static constexpr OSG::Time SHOOTING_TIME = 1.0f;

    OSG::Time getShootingTime() const {
        switch (_selectedWandBulb) {
            case node::THUNDER_BULB:
                return 0.7f;
            case node::WATER_BULB:
                return 0.3f;
            case node::FIRE_BULB:
                return 0.5f;
            default:
                return 1.0f;
        }
    }

    int bulbCount() const;

    void bulbCount(int count);

    void showDefaultBulb();

    void shootBulb();

    void showBulb(magicvr::node::WandBulb bulb);

    magicvr::MagicTricks _tricks;

    virtual void shootLight() = 0;

    virtual void shootWater() = 0;

    virtual void shootFire() = 0;

public:
    AppController();

    virtual void display(OSG::Time dTime);

    virtual void keyboardDown(unsigned char key, int x, int y);

    virtual void keyboardUp(unsigned char key, int x, int y);

    const NodeRecPtr &root() const;

    Scene &scene();

    BezierCurve<> getShootingCurve(input::Tracker wand, OSG::Vec3f destination,
                                       float directionFactor) const;

    void shootLight(input::Tracker tracker);

    void shootWater(input::Tracker tracker, OSG::Vec3f destination);

    void shootFire(input::Tracker tracker, OSG::Vec3f destination);
};

} // namespace magicvr

#endif //MAGICVR_APPCONTROLLER_HPP
