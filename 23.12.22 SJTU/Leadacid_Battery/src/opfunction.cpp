#include "opfunction.h"
using namespace vex;

const int LeftDEADZONE = 5;
const int RightDEADZONE = 5;

void base_movement(){
    Chassis base;
    while(true){
        base.get_controller(127,127);
        if(abs(Controller1.Axis3.position())<=LeftDEADZONE && abs(Controller1.Axis1.position())<=RightDEADZONE){
            base.motor_brake(brake);
        }else{
            base.chassis_movement();
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void takein_control(){
    while(true){
        if(Controller1.ButtonR1.pressing()){
            Takein.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
        }else if(Controller1.ButtonR2.pressing()){
            Takein.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
        }else{
            Takein.stop(brake);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void piston_control(){
    bool pa=false,pb=false,pc=false;
    while(true){
        if(Controller1.ButtonL2.pressing()){
            if(!pa){pa=true;waitUntil(!Controller1.ButtonL2.pressing());}
            else if(pa){pa=false;waitUntil(!Controller1.ButtonL2.pressing());}
        }else if(Controller1.ButtonL1.pressing()){
            if(!pb){pb=true;waitUntil(!Controller1.ButtonL1.pressing());}
            else if(pb){pb=false;waitUntil(!Controller1.ButtonL1.pressing());}
        }else if(Controller1.ButtonA.pressing()){
            pc=true;
        }
        piston1.set(pa);
        piston2.set(pb);
        piston3.set(pc);
        this_thread::sleep_for(UPDATETIME);
    }
}