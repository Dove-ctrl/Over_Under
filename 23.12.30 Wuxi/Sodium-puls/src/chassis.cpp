#include "chassis.h"
using namespace vex;

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
    int adjust=150;
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

void AUTOchassis::set_basic_Linervel_Angularvel(float L,float A){
    Linervel=L;Angularvel=A;
}

void AUTOchassis::set_yagon(float _yagon){yagon=_yagon;}
void AUTOchassis::set_position(float _position){position=_position;}

void AUTOchassis::get_revised_value(float p,float y){
    Revised_L=p;
    Revised_A=y;
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

void AUTOchassis::motor_group_movement(float ReviseL,float ReviseR){
    LF.spin(fwd,ReviseL*((Linervel+Revised_L)+(Angularvel+Revised_A)),voltageUnits::mV);
    RF.spin(fwd,ReviseR*((Linervel+Revised_L)-(Angularvel+Revised_A)),voltageUnits::mV);
    LB.spin(fwd,ReviseL*((Linervel+Revised_L)+(Angularvel+Revised_A)),voltageUnits::mV);
    RB.spin(fwd,ReviseR*((Linervel+Revised_L)-(Angularvel+Revised_A)),voltageUnits::mV);
    LM.spin(fwd,ReviseL*((Linervel+Revised_L)+(Angularvel+Revised_A)),voltageUnits::mV);
    RM.spin(fwd,ReviseR*((Linervel+Revised_L)-(Angularvel+Revised_A)),voltageUnits::mV);
}

void AUTOchassis::resetVelocity(){
    LF.resetPosition();LB.resetPosition();LM.resetPosition();
    RF.resetPosition();RB.resetPosition();RM.resetPosition();
}