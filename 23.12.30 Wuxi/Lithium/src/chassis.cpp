#include "chassis.h"
using namespace vex;
using namespace std;

OPchassis::OPchassis(){
    Linervel=0,Angularvel=0;
}

void OPchassis::chassis_brake(brakeType a){
    LF.stop(a);
    RF.stop(a);
    LB.stop(a);
    RB.stop(a);
    LM.stop(a);
    RM.stop(a);
}

void OPchassis::get_controller(int kl,int ka){
    Linervel = (Controller1.Axis3.position())*kl;
    Angularvel = (Controller1.Axis1.position())*ka;
}

void OPchassis::opchassis_movement(){
    int adjust=300;
    LF.spin(fwd,Linervel+Angularvel,voltageUnits::mV);
    RF.spin(fwd,Linervel-adjust-Angularvel,voltageUnits::mV);
    LB.spin(fwd,Linervel-adjust+Angularvel,voltageUnits::mV);
    RB.spin(fwd,Linervel-Angularvel,voltageUnits::mV);
    LM.spin(fwd,Linervel-adjust+Angularvel,voltageUnits::mV);
    RM.spin(fwd,Linervel-Angularvel,voltageUnits::mV);
}

AUTOchassis::AUTOchassis(){
    Linervel=0,Angularvel=0;
    position=0;yagon=0;
    Revised_A=0;Revised_L=0;
}

void AUTOchassis::reset_sensor(sensor SENSOR){
    switch (SENSOR)
    {
    case VELOCITY:
        LF.resetPosition();LB.resetPosition();LM.resetPosition();
        RF.resetPosition();RB.resetPosition();RM.resetPosition();
        break;
    case INERTIAL:
        Inertial.resetHeading();
        Inertial.setHeading(180,degrees);
        break;
    case ALLSENSOR:
        LF.resetPosition();LB.resetPosition();LM.resetPosition();
        RF.resetPosition();RB.resetPosition();RM.resetPosition();
        Inertial.resetHeading();Inertial.setHeading(180,degrees);
        break;
    default:
        break;
    }
}

void AUTOchassis::set_basic_Linervel_Angularvel(float L,float A){
    Linervel=L;Angularvel=A;
}
void AUTOchassis::set_yagon(float _yagon){yagon=_yagon;}
void AUTOchassis::set_position(float _position){position=_position;}

void AUTOchassis::get_revised_value(float p,float y){
    if(p==0){
        AngularPID.update(y);Revised_A=AngularPID.getoutput();
        Revised_L=0;
    }else if(y==0){
        LinerPID.update(p);Revised_L=LinerPID.getoutput();
        Revised_A=0;
    }else{
        LinerPID.update(p);AngularPID.update(y);
        Revised_L=LinerPID.getoutput();
        Revised_A=AngularPID.getoutput();
    }
}

void AUTOchassis::motor_group_stop(brakeType a){
    LF.stop(a);
    RF.stop(a);
    LB.stop(a);
    RB.stop(a);
    LM.stop(a);
    RM.stop(a);
}

double AUTOchassis::get_current_position(){
     return (fabs(LF.position(deg))+fabs(RF.position(deg))+fabs(RM.position(deg))+
    fabs(LM.position(deg))+fabs(LB.position(deg))+fabs(RB.position(deg)))/6;
}

void AUTOchassis::motor_group_movement(){
    LF.spin(fwd,(Linervel+Revised_L)+(Angularvel+Revised_A),voltageUnits::mV);
    RF.spin(fwd,(Linervel+Revised_L)-(Angularvel+Revised_A),voltageUnits::mV);
    LB.spin(fwd,(Linervel+Revised_L)+(Angularvel+Revised_A),voltageUnits::mV);
    RB.spin(fwd,(Linervel+Revised_L)-(Angularvel+Revised_A),voltageUnits::mV);
    LM.spin(fwd,(Linervel+Revised_L)+(Angularvel+Revised_A),voltageUnits::mV);
    RM.spin(fwd,(Linervel+Revised_L)-(Angularvel+Revised_A),voltageUnits::mV);
}