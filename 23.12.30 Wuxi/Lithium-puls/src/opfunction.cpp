#include "opfunction.h"

void op_movement(void* arg){
    competition* cpt = (competition*)arg;
    OPchassis base;
    while(cpt->isDriverControl()){
        base.get_controller(127,83);
        if(abs(Controller1.Axis3.position())<=LeftDEADZONE && abs(Controller1.Axis1.position())<=RightDEADZONE){
            base.chassis_brake(coast);
        }else{base.opchassis_movement();}
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_arm(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isDriverControl()){
        if(Controller1.ButtonR1.pressing()){
            Arm.spin(fwd,-45,pct);
        }else if(Controller1.ButtonR2.pressing()){
            Arm.spin(reverse,-45,pct);
        }else{
            Arm.stop(hold);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_Spread(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isDriverControl()){
        if(Controller1.ButtonL1.pressing()){
            Spread.spin(fwd,MAXVOLTAGE/1.27,voltageUnits::mV);
        }else if(Controller1.ButtonL2.pressing()){
            Spread.spin(reverse,MAXVOLTAGE/1.27,voltageUnits::mV);
        }else{
            Spread.stop(hold);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_Sidehang(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isDriverControl()){
        if(Controller1.ButtonX.pressing()){
            Hang.spin(fwd,-45,pct);
        }else if(Controller1.ButtonY.pressing()){
            Hang.spin(reverse,-45,pct);
        }else{
            Hang.stop(hold);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}