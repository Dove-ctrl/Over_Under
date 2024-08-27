#include "chassis.h"

OPchassis::OPchassis(){
    liner_velocity=0,angular_velocity=0;
    right_velocity=0;left_velocity=0;
}

int OPchassis::get_deadzone(turnType a){
    if(a==vex::turnType::left){return left_deadzone;}
    else{return right_deadzone;}
}

void OPchassis::get_controller(int liner_adjust,int angular_adjust){
    liner_velocity=liner_adjust*Controller1.Axis3.position();
    angular_velocity=angular_adjust*Controller1.Axis1.position();
    right_velocity=liner_velocity-angular_velocity;
    left_velocity=liner_velocity+angular_velocity;
}

void OPchassis::opchassis_movement(int left_adjust,int right_adjust){
    left_adjust=(liner_velocity>=0 ? left_adjust : -left_adjust);
    right_adjust=(liner_velocity>=0 ? right_adjust : -right_adjust);
    LF.spin(fwd,left_velocity+left_adjust,voltageUnits::mV);
    LB.spin(fwd,left_velocity+left_adjust,voltageUnits::mV);
    LMF.spin(fwd,left_velocity+left_adjust,voltageUnits::mV);
    LMB.spin(fwd,left_velocity+left_adjust,voltageUnits::mV);

    RF.spin(fwd,right_velocity+right_adjust,voltageUnits::mV);
    RB.spin(fwd,right_velocity+right_adjust,voltageUnits::mV);
    RMF.spin(fwd,right_velocity+right_adjust,voltageUnits::mV);
    RMB.spin(fwd,right_velocity+right_adjust,voltageUnits::mV);
}

void OPchassis::opchassis_brake(brakeType a){
    LF.stop(a);LB.stop(a);
    RF.stop(a);RB.stop(a);
    LMF.stop(a);LMB.stop(a);
    RMF.stop(a);RMB.stop(a);
}

void OPchassis::set_deadzone(float ld,float rd){
    left_deadzone=ld,right_deadzone=rd;
}

void OPchassis::set_direction(){
    LF.setReversed(true);
    RF.setReversed(false);
    LB.setReversed(true);
    RB.setReversed(false);
    LMF.setReversed(false);
    LMB.setReversed(false);
    RMF.setReversed(true);
    RMB.setReversed(true);
}

void OPchassis::op_move(void* p){
    competition* _p= (competition*)p;
    OPchassis::getInstance()->set_deadzone(5,5);
    OPchassis::getInstance()->set_direction();
    while(_p->isDriverControl()){
        if(abs(Controller1.Axis3.position())<=OPchassis::getInstance()->get_deadzone(turnType::left) &&
        abs(Controller1.Axis1.position())<=OPchassis::getInstance()->get_deadzone(turnType::right)){
            OPchassis::getInstance()->opchassis_brake(coast);
        }else{    
            OPchassis::getInstance()->get_controller(127,100);
            OPchassis::getInstance()->opchassis_movement(0,0);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void OPchassis::debug_op_move(void* p){
    competition* _p= (competition*)p;
    OPchassis::getInstance()->set_deadzone(5,5);
    OPchassis::getInstance()->set_direction();
    while(_p->isDriverControl()){
        if(abs(Controller1.Axis3.position())<=OPchassis::getInstance()->get_deadzone(turnType::left) &&
        abs(Controller1.Axis1.position())<=OPchassis::getInstance()->get_deadzone(turnType::right)){
            OPchassis::getInstance()->opchassis_brake(coast);
        }else{    
            OPchassis::getInstance()->get_controller(127,100);
            OPchassis::getInstance()->opchassis_movement(0,0);
        }
        this_thread::sleep_for(UPDATETIME);
    }
    /* competition* _p= (competition*)p;
    OPchassis::getInstance()->set_deadzone(5,5);
    while(_p->isDriverControl()){
        Navigation::getInstance()->set_yaw(Inertial.heading());
        if(abs(Controller1.Axis3.position())<=OPchassis::getInstance()->get_deadzone(turnType::left) &&
        abs(Controller1.Axis1.position())<=OPchassis::getInstance()->get_deadzone(turnType::right)){
            OPchassis::getInstance()->opchassis_brake(coast);
        }else{    
            OPchassis::getInstance()->get_controller(127,80);
            OPchassis::getInstance()->opchassis_movement(0,0);
        }
        this_thread::sleep_for(UPDATETIME);
        Navigation::getInstance()->update_position(SCALINGRATIO);
        Brain.Screen.printAt(100,50,"x:%.4f",*(Navigation::getInstance()->get_coordinate()));
        Brain.Screen.printAt(100,100,"y:%.4f",*(Navigation::getInstance()->get_coordinate()+1));
    } */
}