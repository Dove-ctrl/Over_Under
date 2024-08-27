#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "vex.h"
#include "PID.h"

const enum movetype{
    STRIGHT,TURN,CURVE
};

class OPchassis{
    private:
        float Linervel,Angularvel;
    public:
        OPchassis();
        void get_controller(int,int);
        void opchassis_movement();
        void chassis_brake(brakeType);
};

class AUTOchassis{
    private:
        float Linervel,Angularvel;
        float yagon;
        float Revised_L,Revised_A;
        float position;
    public:
        AUTOchassis();
        const enum sensor{
           VELOCITY,INERTIAL,ALLSENSOR
        };
        PID LinerPID; PID_VariableI AngularPID;
        void reset_sensor(sensor);
        void set_basic_Linervel_Angularvel(float,float);
        void set_yagon(float);
        void set_position(float);
        void get_revised_value(float,float);
        double get_current_position();
        void motor_group_movement();
        void motor_group_stop(brakeType);
        void autochassis_movement(float,float,bool,movetype);
        void autochassis_movement(float,float,movetype);
        void turn_around(float);
};

#endif