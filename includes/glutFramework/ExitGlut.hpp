#ifndef MAGICVR_EXITGLUT_HPP
#define MAGICVR_EXITGLUT_HPP

#include <stdexcept>

/**
 * Throw this exception to exit the Glut main loop without exit of application.
 */
class ExitGlut : public std::exception {

};


#endif //MAGICVR_EXITGLUT_HPP
