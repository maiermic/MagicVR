#include <OSGCSM/OSGCAVEConfig.h>
#include "input/RemoteManager.hpp"
#include "util.hpp"

OSG_USING_NAMESPACE

using namespace input;

template<typename T>
T RemoteManager::scale_tracker2cm(const T &value) {
    static const float scale = OSGCSM::convert_length(cfg.getUnits(), 1.f, OSGCSM::CAVEConfig::CAVEUnitCentimeters);
    return value * scale;
}

void VRPN_CALLBACK callbackOnHeadTrackerChange(void *remoteManager, const vrpn_TRACKERCB tracker) {
    ((RemoteManager*) remoteManager)->onHeadTrackerChange(tracker);
}

void RemoteManager::onHeadTrackerChange(const vrpn_TRACKERCB tracker) {
    head.orientation = util::arrayToQuaternion(tracker.quat);
    head.position = Vec3f(scale_tracker2cm(Vec3d(tracker.pos)));
}

void VRPN_CALLBACK callbackOnWandTrackerChange(void *remoteManager, const vrpn_TRACKERCB tracker) {
    ((RemoteManager*) remoteManager)->onWandTrackerChange(tracker);
}

void VRPN_CALLBACK RemoteManager::onWandTrackerChange(const vrpn_TRACKERCB tracker) {
    wand.orientation = util::arrayToQuaternion(tracker.quat);
    wand.position = Vec3f(scale_tracker2cm(Vec3d(tracker.pos)));
}

void VRPN_CALLBACK callbackOnButtonChange(void *remoteManager, const vrpn_BUTTONCB button) {
    ((RemoteManager*) remoteManager)->onButtonChange(button);
}

void VRPN_CALLBACK RemoteManager::onButtonChange(const vrpn_BUTTONCB button) {
    const auto buttonNumber = (unsigned long) button.button;
    if (0 <= buttonNumber && buttonNumber < buttons.size()) {
        buttons[buttonNumber] = (bool) button.state;
    } else {
        std::cerr << "unknown wand button " << buttonNumber << '\n';
    }
}

void VRPN_CALLBACK callbackOnAnalogChange(void *remoteManager, const vrpn_ANALOGCB analog) {
    ((RemoteManager*) remoteManager)->onAnalogChange(analog);
}

void VRPN_CALLBACK RemoteManager::onAnalogChange(const vrpn_ANALOGCB analog) {
    if (analog.num_channel >= 2)
        analog_values = Vec3f(analog.channel[0], 0, -analog.channel[1]);
}

RemoteManager::RemoteManager(OSGCSM::CAVEConfig &cfg)
        : cfg(cfg), buttons() {
    head.orientation = Quaternion(Vec3f(0.f, 1.f, 0.f), 3.141f);
    // a 1.7m Person 2m in front of the scene
    head.position = Vec3f(0.f, 170.f, 200.f);
    try {
        const char *const vrpn_name = "DTrack@localhost";
        tracker = new vrpn_Tracker_Remote(vrpn_name);
        tracker->shutup = true;
        tracker->register_change_handler(
                this,
                callbackOnHeadTrackerChange,
                cfg.getSensorIDHead()
            );
        tracker->register_change_handler(
                this,
                callbackOnWandTrackerChange,
                cfg.getSensorIDController()
            );
        button = new vrpn_Button_Remote(vrpn_name);
        button->shutup = true;
        button->register_change_handler(
                this,
                callbackOnButtonChange
            );
        analog = new vrpn_Analog_Remote(vrpn_name);
        analog->shutup = true;
        analog->register_change_handler(
                this,
                callbackOnAnalogChange
            );
    }
    catch (const std::exception &e) {
        std::cout << "ERROR: " << e.what() << '\n';
        return;
    }
}

RemoteManager::~RemoteManager() {
    delete tracker;
    delete button;
    delete analog;
}

void RemoteManager::check_tracker() {
    tracker->mainloop();
    button->mainloop();
    analog->mainloop();
}

void RemoteManager::print_tracker() {
    std::cout << "Head position: " << head.position << " orientation: " << head.orientation << '\n';
    std::cout << "Wand position: " << wand.position << " orientation: " << wand.orientation << '\n';
    std::cout << "Analog: " << analog_values << '\n';
}

