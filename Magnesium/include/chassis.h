#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "vex.h"

using namespace vex;

class OPchassis{
private:
    float left_velocity , right_velocity;
    float liner_velocity , angular_velocity;
public:
    int left_deadzone , right_deadzone;
    OPchassis();
    void opchassis_movement();
    void get_controller();
    void set_deadzone(float ld,float rd);
    void opchassis_brake(brakeType);
};

#endif