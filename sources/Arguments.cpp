#include <cstring>

#include "Arguments.hpp"


Arguments::Arguments(int argc, char **argv) {
    for (int a = 1; a < argc; ++a) {
        if (argv[a][0] == '-') {
            if (strcmp(argv[a], "-f") == 0) {
                configurationFile = argv[a][2] ? &argv[a][2] : &argv[++a][0];
            }
        } else {
            sceneFile = argv[a];
        }
    }
}
