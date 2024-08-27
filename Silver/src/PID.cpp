#include "PID.h"

PID::PID(){
    first_time=true;
    arrived=false;
}

void PID::reset(reset_type a){
    switch (a)
    {
    case _first_time:
        first_time=false;
        break;
    case _I:
        I=0;
        break;
    case _arrived:
        arrived=false;
        break;
    case _all:
        first_time=false;I=0;arrived=false;
        break;
    default:
        break;
    }
}

void PID::set_coefficient(float _kp,float _ki,float _kd){
    kp=_kp;
    ki=_ki;
    kd=_kd;
}
void PID::set_error_tol(float _error_tol){error_tol=_error_tol;}
void PID::set_error_range(float _error_range_low,float _error_range_high){
    error_range_low = _error_range_low;
    error_range_high = _error_range_high;
}
void PID::set_target(float _target){target=_target;}
bool PID::target_arrived(){return arrived;}
float PID::get_output(){return output;}

void PID::update(float input){
    error_curt = target-input;
    if(fabs(error_curt)<=error_tol){
        arrived=true;
        output = 0;
    }
    if(first_time){
        first_time=false;
        error_past=error_curt;
        error_I=0;
    }

    P = error_curt * kp;

    error_I = error_I + error_curt;
    I = error_I * ki;
    if(error_curt == 0 || error_curt > error_range_high || error_curt < error_range_low){
        I = 0;
    }

    error_D=error_curt-error_past;
    D=error_D * kd;

    error_past=error_curt;

    output = P+I+D;
}