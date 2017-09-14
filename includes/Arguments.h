#ifndef MYPROJECT_ARGUMENTS_H
#define MYPROJECT_ARGUMENTS_H


class Arguments {
public:
    const char *configurationFile = nullptr;
    const char *sceneFile = nullptr;
    Arguments(int argc, char **argv);
};


#endif //MYPROJECT_ARGUMENTS_H
