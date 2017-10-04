#ifndef MAGICVR_SIMPLESCENEMANAGERNAVIGATOR_HPP
#define MAGICVR_SIMPLESCENEMANAGERNAVIGATOR_HPP


#include <OpenSG/OSGSimpleSceneManager.h>

namespace magicvr {
    class SimpleSceneManagerNavigator {
        OSG::SimpleSceneManagerRefPtr _mgr;
        bool _isMovingBackwards;
        bool _isMovingForwards;

    public:
        SimpleSceneManagerNavigator();

        void keyboardDown(unsigned char key);

        void keyboardUp(unsigned char key);

        void update();

        void simpleSceneManager(const OSG::SimpleSceneManagerRefPtr &mgr);
    };
}

#endif //MAGICVR_SIMPLESCENEMANAGERNAVIGATOR_HPP
