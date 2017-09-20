#ifndef MAGICVR_MAGICVRAPP_HPP
#define MAGICVR_MAGICVRAPP_HPP

#include <inVRs/tools/libraries/OpenSGApplicationBase/OpenSGApplicationBase.h>

class MagicVrApp : public OpenSGApplicationBase {
private:
    std::string defaultConfigFile;

protected:
    std::string getConfigFile(const CommandLineArgumentWrapper &args) override;

    bool initialize(const CommandLineArgumentWrapper &args) override;

    void cleanup() override;

    void display(float dt) override;

public:
    MagicVrApp();
    ~MagicVrApp();
};


#endif //MAGICVR_MAGICVRAPP_HPP
