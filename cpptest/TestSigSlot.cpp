//
// Created by chen.chen on 2018/9/14.
//

#include <iostream>
#include "sigslot/sigslot.h"


class Switch {
public:
    explicit Switch(const std::string& name): mName(name)
    {

    }

    sigslot::signal0<> mSwitchSignal;

private:
    std::string mName;
};

class Light : public sigslot::has_slots<> {
public:
    explicit Light(const std::string& name): mName(name), mIsOn(false)
    {

    }

    void toggle()
    {
        mIsOn = !mIsOn;
        std::cout << "Toggle light '" << mName << "' to " << (mIsOn ? "Yes" : "No") << std::endl;
    }

private:
    std::string mName;
    bool mIsOn;
};

class Fan : public sigslot::has_slots<> {
public:
    explicit Fan(const std::string& name): mName(name), mFanSpeed(0)
    {

    }

    void turn()
    {
        mFanSpeed++;
        if (mFanSpeed == 5) {
            mFanSpeed = 0;
        }
        std::cout << "Turn fun '" << mName << "' to " << mFanSpeed << std::endl;
    }

private:
    std::string mName;
    int mFanSpeed;
};

int main()
{
    Switch aSwitch("Switch1");
    Switch bSwitch("Switch2");
    Light aLight("Light1");
    Light bLight("Light2");
    Light cLight("Light3");
    Fan aFun("Fan");

    aSwitch.mSwitchSignal.connect(&aLight, &Light::toggle);
    aSwitch.mSwitchSignal.connect(&aFun, &Fan::turn);
    bSwitch.mSwitchSignal.connect(&bLight, &Light::toggle);
    bSwitch.mSwitchSignal.connect(&cLight, &Light::toggle);

    for (int i = 0; i < 10; ++i) {
        std::cout << "switch press " << i << "==========================" << std::endl;
        aSwitch.mSwitchSignal.emit();
        bSwitch.mSwitchSignal.emit();
    }
}