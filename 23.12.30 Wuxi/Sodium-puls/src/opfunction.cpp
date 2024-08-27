#include "opfunction.h"

void op_movement(void* arg){
    competition* cpt = (competition*)arg;
    OPchassis base;
    while(cpt->isDriverControl()){
        base.get_controller(127,85);
        if(abs(Controller1.Axis3.position())<=LeftDEADZONE && abs(Controller1.Axis1.position())<=RightDEADZONE){
            base.chassis_brake(coast);
        }else{base.opchassis_movement();}
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_takein(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isDriverControl()){
        if(Controller1.ButtonR1.pressing()){Takein.spin(fwd,MAXVOLTAGE,voltageUnits::mV);}
        else if(Controller1.ButtonR2.pressing()){Takein.spin(reverse,MAXVOLTAGE,voltageUnits::mV);}
        else{Takein.stop(brake);}
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_arm(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isDriverControl()){
        if(Controller1.ButtonB.pressing()){
            ArmL.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
            ArmR.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
        }else if(Controller1.ButtonX.pressing()){
            ArmL.spin(fwd,-MAXVOLTAGE,voltageUnits::mV);
            ArmR.spin(fwd,-MAXVOLTAGE,voltageUnits::mV);
        }else{ArmL.stop(hold);ArmR.stop(hold);}
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_piston_control(void* arg){
    competition* cpt = (competition*)arg;
    bool pl=false,pr=false,pt=false;
    while(cpt->isDriverControl()){
        if(Controller1.ButtonL2.pressing()){
            if(!pr){pr=true;waitUntil(!Controller1.ButtonL2.pressing());}
            else if(pr){pr=false;waitUntil(!Controller1.ButtonL2.pressing());}
        }else if(Controller1.ButtonL1.pressing()){
            if(!pl){pl=true;waitUntil(!Controller1.ButtonL1.pressing());}
            else if(pl){pl=false;waitUntil(!Controller1.ButtonL1.pressing());}
        }else if(Controller1.ButtonA.pressing()){pt=true;}
        Piston_triger.set(pt);
        Piston_left.set(pl);Piston_right.set(pr);
    }
}