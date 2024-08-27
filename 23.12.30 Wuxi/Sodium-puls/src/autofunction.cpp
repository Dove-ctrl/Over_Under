#include "autofunction.h"
using namespace std;

bool take_in = false;
bool take_out = false;
bool piston_left = false;
bool piston_right = false;

void auto_take(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isAutonomous()){
        if(take_in){Takein.spin(fwd,MAXVOLTAGE,voltageUnits::mV);}
        else if(take_out){Takein.spin(reverse,MAXVOLTAGE,voltageUnits::mV);}
        else{Takein.stop(brake);}
        this_thread::sleep_for(UPDATETIME);
    }
}

void auto_piston(void* arg){
    competition* cpt = (competition*)arg;
    while(cpt->isAutonomous()){
        Piston_left.set(piston_left);
        Piston_right.set(piston_right);
        this_thread::sleep_for(UPDATETIME);
    }
}

void AUTOchassis::forward(float v,float pos){
    resetVelocity();
    v=(v/100)*MAXVOLTAGE; pos=1500*pos;
    PID posPID; timer T; T.clear();
    posPID.setCoefficient(2,0.001,3.2);
    posPID.seterrorTol(0.5);
    posPID.setIrange(0.01,1500);
    posPID.setMaxtime(10000);
    posPID.setTarget(pos);
    set_basic_Linervel_Angularvel(v,0);
    do{
        posPID.update(get_current_position());
        get_revised_value(posPID.getoutput(),0);
        motor_group_movement(0.98,1);
        wait(UPDATETIME,msec);
        if(T.time(msec)>=3000){break;}
    }while(fabs(get_current_position())<=pos);
    motor_group_stop(brake);
    posPID.resetfirstTime();posPID.resetI();
    posPID.resetoutput();posPID.resetTimer();
}

void AUTOchassis::backward(float v,float pos){
    resetVelocity();
    v=(v/100)*MAXVOLTAGE; pos=1507*pos;
    PID posPID;timer T; T.clear();
    posPID.setCoefficient(2,0.001,3.2);
    posPID.seterrorTol(0.5);
    posPID.setIrange(0.01,1500);
    posPID.setMaxtime(10000);
    posPID.setTarget(-pos);
    set_basic_Linervel_Angularvel(-v,0);
    do{
        posPID.update(get_current_position());
        get_revised_value(posPID.getoutput(),0);
        motor_group_movement(0.98,1);
        wait(UPDATETIME,msec);
        if(T.time(msec)>=3000){break;}
    }while(fabs(get_current_position())<=pos);
    motor_group_stop(brake);
    posPID.resetfirstTime();posPID.resetI();
    posPID.resetoutput();posPID.resetTimer();
}

void AUTOchassis::turn_left(float yagon){
    yagon=yagon+13;
    yagon=180-yagon;
    PID anglePID;timer T;
    T.clear();
    anglePID.setCoefficient(300,30,2100);
    anglePID.seterrorTol(0.6);
    anglePID.setIrange(0.01,5000);
    anglePID.setTarget(yagon);
    set_basic_Linervel_Angularvel(0,0);
    do{
        anglePID.update(Inertial.heading());
        get_revised_value(0,anglePID.getoutput());
        motor_group_movement(1,1);
        cout<<Inertial.heading()<<endl;
        wait(UPDATETIME,msec);
        if(fabs(Inertial.heading()-yagon-13)<=3 || T.value()>=1.5){break;}
    }while(1);
    motor_group_stop(brake);
    anglePID.resetfirstTime();anglePID.resetI();
    anglePID.resetoutput();anglePID.resetTimer();
}

void AUTOchassis::turn_right(float yagon){
    yagon=yagon-17;
    yagon=yagon+180;
    PID anglePID;timer T;
    T.clear();
    anglePID.setCoefficient(300,30,2100);
    anglePID.seterrorTol(0.6);
    anglePID.setIrange(0.01,5000);
    anglePID.setTarget(yagon);
    set_basic_Linervel_Angularvel(0,0);
    do{
        anglePID.update(Inertial.heading());
        get_revised_value(0,anglePID.getoutput());
        motor_group_movement(1,1);
        wait(UPDATETIME,msec);
        cout<<Inertial.heading()<<endl;
        if(fabs(Inertial.heading()-yagon-17)<=3 || T.value()>=1.5){break;}
    }while(1);
    motor_group_stop(brake);
    anglePID.resetfirstTime();anglePID.resetI();
    anglePID.resetoutput();anglePID.resetTimer();
}