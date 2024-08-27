#include "control-lib.h"

bool in = false , out = false ;
bool lf = false , rf = false ;
bool lb = false , rb = false ;

void op_takein(void* p){
    competition* _p = (competition*)p;
    bool _in , _out ;
    while(_p->isDriverControl()){
        _in = Controller1.ButtonL2.pressing(); _out = Controller1.ButtonL1.pressing();
        Takein.spin(fwd,(_in - _out)*MAXVOLTAGE,voltageUnits::mV);
        this_thread::sleep_for(UPDATETIME);
    }
}

void auto_takein(void* p){
    competition* _p = (competition*)p;
    while(_p->isAutonomous()){
        if(in){Takein.spin(reverse,MAXVOLTAGE,voltageUnits::mV);}
        else if(out){Takein.spin(fwd,MAXVOLTAGE,voltageUnits::mV);}
        else{Takein.stop(brake);}
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_piston(void* p){
    competition* _p = (competition*)p;
    bool pl = false,pr = false,plb = false,prb = false;
    while(_p->isDriverControl()){
        if(Controller1.ButtonY.pressing()){
            if(!pr){pr = true;waitUntil(!Controller1.ButtonY.pressing());}
            else if(pr){pr = false;waitUntil(!Controller1.ButtonY.pressing());}
        }else if(Controller1.ButtonRight.pressing()){
            if(!pl){pl = true;waitUntil(!Controller1.ButtonRight.pressing());}
            else if(pl){pl = false;waitUntil(!Controller1.ButtonRight.pressing());}
        }else if(Controller1.ButtonDown.pressing()){
            if(!plb){plb = true;waitUntil(!Controller1.ButtonDown.pressing());}
            else if(plb){plb = false;waitUntil(!Controller1.ButtonDown.pressing());}
        }else if(Controller1.ButtonB.pressing()){
            if(!prb){prb = true;waitUntil(!Controller1.ButtonB.pressing());}
            else if(prb){prb = false;waitUntil(!Controller1.ButtonB.pressing());}
        }
        LFPiston.set(pl);RFPiston.set(pr);
        LBPiston.set(plb);RBPiston.set(prb);
        this_thread::sleep_for(UPDATETIME);
    }
}

void auto_piston(void* p){
    competition* _p = (competition*)p;
    while(_p->isAutonomous()){
        LFPiston.set(lf);RFPiston.set(rf);
        LBPiston.set(lb);RBPiston.set(rb);
        this_thread::sleep_for(UPDATETIME);
    }
}

void op_hang(void* p){
    competition* _p = (competition*)p;
    while(_p->isDriverControl()){
        Lhang.spin(fwd,MAXVOLTAGE * (Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing()),voltageUnits::mV);
        Rhang.spin(fwd,MAXVOLTAGE * (Controller1.ButtonR1.pressing() - Controller1.ButtonR2.pressing()),voltageUnits::mV);
        this_thread::sleep_for(UPDATETIME);
    }
}