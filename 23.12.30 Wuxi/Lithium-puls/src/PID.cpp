#include "PID.h"
using namespace vex;

PID::PID(){
    firstTime=true;
    arrived=false;
    output=0;
    T.clear();
}

void PID::setCoefficient(float _kp,float _ki,float _kd){
    kp=_kp;
    ki=_ki;
    kd=_kd;
}

void PID::setTarget(float _target){target=_target;}
void PID::seterrorTol(float _errorTol){errorTol=_errorTol;}
void PID::setIrange(float max,float min){IMax=max;IMin=min;}
bool PID::targetArrived(){return arrived;}
float PID::getoutput(){return output;}
void PID::resetI(){I=0;}
void PID::resetoutput(){output=0;}
void PID::resetfirstTime(){firstTime=false;}
void PID::setMaxtime(float t){maxtime=t;}
void PID::resetTimer(){T.clear();}

void PID::update(float input){
    errorCurt=target-input;
    if(fabs(errorCurt)<=errorTol || maxtime<=T.time(msec)){
        arrived=true;
        resetI();
        resetTimer();
    }
    if(firstTime){
        firstTime=false;
        errorP=errorCurt;
        errorI=0;
        resetTimer();
    }

    //Calculate P
    P=errorCurt*kp;

    //Calculate D
    errorD=errorCurt-errorP;
    errorP=errorCurt;//record current error for next time calculation
    D=errorD*kd;

    //Calculate I
    errorI=I+errorCurt;
    I=errorI*ki;
    if(I<IMin)I=IMin;
    else if(I>IMax)I=IMax;
    
    //Calculate PID
    output=P+I+D;
}

void PID_VariableI::set_variable_param(float phase,float smooth){
    Phase=phase;Smooth=smooth;
}

float PID_VariableI::variable(float errori){
    return 1 / (1 + exp( Smooth * ( Phase - errori )));//logistic function
}

void PID_VariableI::update(float input){
    errorCurt=target-input;
    if(fabs(errorCurt)<=errorTol){
        arrived=true;
        resetI();
        resetTimer();
    }
    if(firstTime){
        firstTime=false;
        errorP=errorCurt;
        errorI=0;
        resetTimer();
    }

    //Calculate P
    P=errorCurt*kp;

    //Calculate D
    errorD=errorCurt-errorP;
    errorP=errorCurt;//record current error for next time calculation
    D=errorD*kd;

    //Calculate I
    errorI=I+variable(errorCurt)*errorCurt;
    I=errorI*ki;
    if(I<IMin)I=IMin;
    else if(I>IMax)I=IMax;
    
    
    //Calculate PID
    output=P+I+D;
}