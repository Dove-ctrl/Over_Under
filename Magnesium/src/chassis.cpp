#include "chassis.h"

OPchassis::OPchassis(){
    left_velocity=0,right_velocity=0;
    left_deadzone=5,right_deadzone=5;
    liner_velocity=0,angular_velocity=0;
}

void OPchassis::get_controller(){
    liner_velocity=127.5*Controller1.Axis3.position();
    angular_velocity=127.5*Controller1.Axis1.position();
    left_velocity=liner_velocity+angular_velocity;
    right_velocity=liner_velocity-angular_velocity;
}

void OPchassis::opchassis_movement(){
    LF.spin(fwd,left_velocity,voltageUnits::mV);
    LB.spin(fwd,left_velocity,voltageUnits::mV);
    LF.spin(fwd,left_velocity,voltageUnits::mV);
    RF.spin(fwd,right_velocity,voltageUnits::mV);
    RB.spin(fwd,right_velocity,voltageUnits::mV);
    RM.spin(fwd,right_velocity,voltageUnits::mV);
}

void OPchassis::opchassis_brake(brakeType a){
    LF.stop(a);LB.stop(a);LM.stop(a);
    RF.stop(a);RB.stop(a);RM.stop(a);
}

void OPchassis::set_deadzone(float ld,float rd){
    left_deadzone=ld,right_deadzone=rd;
}