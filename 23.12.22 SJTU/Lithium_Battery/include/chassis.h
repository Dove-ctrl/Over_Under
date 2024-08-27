#ifndef CHASSIS_H_
#define CHASSIS_H_
#include "vex.h"
#include "PID.h"

class Chassis{
    protected:
        float LinerVel,AngularVel;
    public:
        Chassis();
        void get_controller(int,int);//get controller data and convert it to voltage
        virtual void chassis_movement();
        void motor_brake(vex::brakeType);
};

class ChassisAuto : public Chassis{
    private:
        float Heading;//yagon
        float Revised_L,Revised_A;
    public:
        timer T;
        PID Line;PID_VariableI Angle;
        PID_VariableI VisionX;PID_VariableI VisionY;
        const enum sensor{
            _MOTOR,_VELOCITY,_INERTIAL,_TIMER,_ALLSENSOR
        };
        void reset(sensor);//choose a sensor to reset itself
        void set_LinerVel_AngularVel(float,float);
        void set_yagon(float);
        void get_revised_value(float,float);
        void chassis_movement();//the real velocity of motor is setting value + revised value(PID)
};

#endif