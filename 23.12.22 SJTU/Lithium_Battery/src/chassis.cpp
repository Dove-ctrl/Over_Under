#include "chassis.h"
using namespace vex;

Chassis::Chassis(){
    LinerVel=0;AngularVel=0;
}

void Chassis::get_controller(int kl,int ka){
    LinerVel = (Controller1.Axis3.position())*kl;
    AngularVel = (Controller1.Axis1.position())*ka;
}

void Chassis::motor_brake(vex::brakeType a){
    LF.stop(a);
    RF.stop(a);
    LB.stop(a);
    RB.stop(a);
    LU.stop(a);
    RU.stop(a);
}

void Chassis::chassis_movement(){
    LF.spin(fwd,LinerVel+AngularVel,voltageUnits::mV);
    LB.spin(fwd,LinerVel+AngularVel,voltageUnits::mV);
    LU.spin(fwd,LinerVel+AngularVel,voltageUnits::mV);
    RF.spin(fwd,LinerVel-AngularVel,voltageUnits::mV);
    RB.spin(fwd,LinerVel-AngularVel,voltageUnits::mV);
    RU.spin(fwd,LinerVel-AngularVel,voltageUnits::mV);
}

void ChassisAuto::reset(sensor SENSOR){
    switch (SENSOR)
    {
    case _MOTOR:
        LF.stop(brake);LB.stop(brake);LU.stop(brake);
        RF.stop(brake);RB.stop(brake);RU.stop(brake);
        break;
    case _VELOCITY:
        LF.resetPosition();LB.resetPosition();LU.resetPosition();
        RF.resetPosition();RB.resetPosition();RU.resetPosition();
        break;
    case _INERTIAL:
        INERTIAL.resetHeading();
        break;
    case _TIMER:
        T.clear();
        break;
    case _ALLSENSOR:
        T.clear();
        LF.resetPosition();LB.resetPosition();LU.resetPosition();
        RF.resetPosition();RB.resetPosition();RU.resetPosition();
        INERTIAL.resetHeading();
        break;
    default:
        break;
    }
}

void ChassisAuto::set_LinerVel_AngularVel(float L,float A){LinerVel=L;AngularVel=A;}
void ChassisAuto::set_yagon(float yagon){Heading=yagon;}
void ChassisAuto::get_revised_value(float rl,float ra){Revised_A=ra,Revised_L=rl;}

void ChassisAuto::chassis_movement(){
    LF.spin(fwd,(LinerVel+Revised_L)+(AngularVel+Revised_A),voltageUnits::mV);
    LB.spin(fwd,(LinerVel+Revised_L)+(AngularVel+Revised_A),voltageUnits::mV);
    LU.spin(fwd,(LinerVel+Revised_L)+(AngularVel+Revised_A),voltageUnits::mV);
    RF.spin(fwd,(LinerVel+Revised_L)-(AngularVel+Revised_A),voltageUnits::mV);
    RB.spin(fwd,(LinerVel+Revised_L)-(AngularVel+Revised_A),voltageUnits::mV);
    RU.spin(fwd,(LinerVel+Revised_L)-(AngularVel+Revised_A),voltageUnits::mV);
}