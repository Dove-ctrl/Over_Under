#ifndef CONTROL_LIB_H_
#define CONTROL_LIB_H_

#include "vex.h"
#include "math-lib.h"

/* chassis */

class Chassis{
protected:
    float yaw;
    float vel_list[4];
    float center_vel_y , center_vel_x;
    float world_vel_y , world_vel_x;
    float angular_vel;
    float R;
    double sin_yaw , cos_yaw;
public:
    Chassis(float _yaw , float _R);
    void set_vel_list(float * vel);
    void set_brake_type(vex::brakeType type_a);
    void chassis_movement();
};

class OPChassis : public Chassis{
public:
    void get_controller(float Y_dead_zone , float X_dead_zone , float angluar_dead_zone);
    void op_chassis_movement_by_car();
    void op_chassis_movement_by_man();
};

class AutoChassis : public Chassis{
public:
    void route();
    void auto_chassis_movement();
};

#endif