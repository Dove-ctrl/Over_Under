#include "chassis.h"

/* void AUTOchassis::path_tracking(int loop_times){
    
} */

AUTOchassis::AUTOchassis(){
    liner_velocity = 0 , angular_velocity = 0;
    velocity = 0;
    position = 0;
    wheel_distance = 2.7;
    current_yaw.value = 0;
    T.clear();
}

float AUTOchassis::output_limit(float limit , float input){
    return (fabs(input) > limit ? sign(input)*limit : input);
}

float AUTOchassis::get_position(){return (fabs(LB.position(degrees)) + fabs(RB.position(degrees))) / 2;}
float AUTOchassis::get_velocity(){return (fabs(LB.velocity(velocityUnits::rpm)) + fabs(LB.velocity(velocityUnits::rpm))) / 2;}
float AUTOchassis::get_yaw(){return fabs(Inertial.rotation());}

void AUTOchassis::reset_postion(){
    LB.resetPosition();
    RB.resetPosition();
}

void AUTOchassis::reset_inertial(){
    Inertial.resetRotation();
}

void AUTOchassis::autochassis_movement(int left_adjust , int right_adjust , bool reverse){
    LF.setReversed(!reverse);
    RF.setReversed(reverse);
    LB.setReversed(!reverse);
    RB.setReversed(reverse);
    LMF.setReversed(reverse);
    LMB.setReversed(reverse);
    RMF.setReversed(!reverse);
    RMB.setReversed(!reverse);

    LF.spin(fwd,liner_velocity + angular_velocity + left_adjust,voltageUnits::mV);
    LB.spin(fwd,liner_velocity + angular_velocity + left_adjust,voltageUnits::mV);
    LMF.spin(fwd,liner_velocity + angular_velocity + left_adjust,voltageUnits::mV);
    LMB.spin(fwd,liner_velocity + angular_velocity + left_adjust,voltageUnits::mV);

    RF.spin(fwd,liner_velocity - angular_velocity + right_adjust,voltageUnits::mV);
    RB.spin(fwd,liner_velocity - angular_velocity + right_adjust,voltageUnits::mV);
    RMF.spin(fwd,liner_velocity - angular_velocity + right_adjust,voltageUnits::mV);
    RMB.spin(fwd,liner_velocity - angular_velocity + right_adjust,voltageUnits::mV);
}

void AUTOchassis::autochassis_brake(brakeType a){
    LF.stop(a);LB.stop(a);
    RF.stop(a);RB.stop(a);
    LMF.stop(a);LMB.stop(a);
    RMF.stop(a);RMB.stop(a);
}

void AUTOchassis::forward(float vel , float d){
    position = d * 1281;
    velocity = ((vel >= 100 ? 100 : vel) / 100) * MAXRPM;
    liner_position_pid.set_target(position); liner_position_pid.set_error_range(5,position);
    liner_velocity_pid.set_error_range(100,0.95*velocity);
    T.clear();
    reset_postion();
    while(!liner_position_pid.target_arrived() /* && T.time(msec) <= MAXMOVETIME */){
        liner_position_pid.update(get_position());

        liner_velocity_pid.set_target(liner_position_pid.get_output());
        liner_velocity_pid.update(get_velocity());
        liner_velocity = velocity / MAXRPM * output_limit(MAXVOLTAGE , liner_velocity_pid.get_output());
        angular_velocity = 0;
        autochassis_movement(0,0,false);
        wait(UPDATETIME,msec);
    }
    autochassis_brake(coast);
    liner_velocity_pid.reset(liner_velocity_pid._all);
    liner_position_pid.reset(liner_position_pid._all);
}

void AUTOchassis::backward(float vel , float d){
    position = d * 1281;
    velocity = ((vel >= 100 ? 100 : vel) / 100) * MAXRPM;
    liner_position_pid.set_target(position); liner_position_pid.set_error_range(5,position);
    liner_velocity_pid.set_error_range(100,0.95*velocity);
    T.clear();
    reset_postion();
    while(!liner_position_pid.target_arrived() && T.time(msec) <= MAXMOVETIME){
        liner_position_pid.update(get_position());
        liner_velocity_pid.set_target(liner_position_pid.get_output());
        liner_velocity_pid.update(get_velocity());
        liner_velocity = velocity / MAXRPM * output_limit(MAXVOLTAGE , liner_velocity_pid.get_output());
        angular_velocity = 0;
        autochassis_movement(0,0,true);
        wait(UPDATETIME,msec);
    }
    autochassis_brake(coast);
    liner_velocity_pid.reset(liner_velocity_pid._all);
    liner_position_pid.reset(liner_position_pid._all);
}

void AUTOchassis::turn_left_to(float vel , float angle){
    current_yaw.value = Inertial.heading();
    angle = current_yaw - angle;
    velocity = ((vel >= 100 ? 100 : vel) / 100) * MAXRPM;
    angular_position_pid.set_target(angle); angular_position_pid.set_error_range(2,angle);
    angular_velocity_pid.set_error_range(100,0.95*velocity);
    T.clear();
    reset_inertial();
    while(!angular_position_pid.target_arrived() && T.time(msec) <= MAXMOVETIME){
        angular_position_pid.update(get_yaw());
        angular_velocity_pid.set_target(angular_position_pid.get_output());
        angular_velocity_pid.update(get_velocity());
        liner_velocity = 0;
        angular_velocity = velocity / MAXRPM * output_limit(MAXVOLTAGE , angular_velocity_pid.get_output());
        autochassis_movement(0,0,true);
        wait(UPDATETIME,msec);
        
    }
    autochassis_brake(coast);
    angular_position_pid.reset(angular_position_pid._all);
    angular_velocity_pid.reset(angular_velocity_pid._all);
}

void AUTOchassis::turn_right_to(float vel , float angle){
    current_yaw.value = Inertial.heading();
    angle = current_yaw + angle;
    velocity = ((vel >= 100 ? 100 : vel) / 100) * MAXRPM;
    angular_position_pid.set_target(angle); angular_position_pid.set_error_range(2,angle);
    angular_velocity_pid.set_error_range(100,0.95*velocity);
    T.clear();
    reset_inertial();
    while(!angular_position_pid.target_arrived() && T.time(msec) <= MAXMOVETIME){
        angular_position_pid.update(get_yaw());
        angular_velocity_pid.set_target(angular_position_pid.get_output());
        angular_velocity_pid.update(get_velocity());
        liner_velocity = 0;
        angular_velocity = velocity / MAXRPM * output_limit(MAXVOLTAGE , angular_velocity_pid.get_output());
        autochassis_movement(0,0,false);
        wait(UPDATETIME,msec);
        
    }
    autochassis_brake(coast);
    angular_position_pid.reset(angular_position_pid._all);
    angular_velocity_pid.reset(angular_velocity_pid._all);
}

void AUTOchassis::left_curve(float vel , float angle , float ratio){
    current_yaw.value = Inertial.heading();
    if(vel >= 0){
        angle = current_yaw - angle;
    }else{
        angle = current_yaw + angle;
    }
    velocity = ((vel >= 100 ? 100 : vel) / 100) * MAXRPM;
    angular_position_pid.set_target(angle); angular_position_pid.set_error_range(2,angle);
    angular_velocity_pid.set_error_range(100,0.95*velocity);
    T.clear();
    reset_inertial();
    while(!angular_position_pid.target_arrived() && T.time(msec) <= MAXMOVETIME){
        angular_position_pid.update(get_yaw());
        angular_velocity_pid.set_target(angular_position_pid.get_output());
        angular_velocity_pid.update(get_velocity());
        angular_velocity = velocity / MAXRPM * output_limit(MAXVOLTAGE , angular_velocity_pid.get_output());
        liner_velocity = -angular_velocity * fabs(ratio);
        autochassis_movement(0,0,true);
        wait(UPDATETIME,msec);
    }
    autochassis_brake(coast);
    angular_position_pid.reset(angular_position_pid._all);
    angular_velocity_pid.reset(angular_velocity_pid._all);
}

void AUTOchassis::right_curve(float vel , float angle , float ratio){
    current_yaw.value = Inertial.heading();
    if(vel >= 0){
        angle = current_yaw + angle;
    }else{
        angle = current_yaw - angle;
    }
    velocity = ((vel >= 100 ? 100 : vel) / 100) * MAXRPM;
    angular_position_pid.set_target(angle); angular_position_pid.set_error_range(2,angle);
    angular_velocity_pid.set_error_range(100,0.95*velocity);
    T.clear();
    reset_inertial();
    while(!angular_position_pid.target_arrived() && T.time(msec) <= MAXMOVETIME){
        angular_position_pid.update(get_yaw());
        angular_velocity_pid.set_target(angular_position_pid.get_output());
        angular_velocity_pid.update(get_velocity());
        angular_velocity = velocity / MAXRPM * output_limit(MAXVOLTAGE , angular_velocity_pid.get_output());
        liner_velocity = angular_velocity * fabs(ratio);
        autochassis_movement(0,0,false);
        wait(UPDATETIME,msec);
    }
    autochassis_brake(coast);
    angular_position_pid.reset(angular_position_pid._all);
    angular_velocity_pid.reset(angular_velocity_pid._all);
}

void AUTOchassis::debug_run_auto(void* p){
    competition* cpt = (competition*)p;

    timer route_timer;

    thread(auto_piston,cpt);
    thread(auto_takein,cpt);

    liner_velocity_pid.set_coefficient(2, 0 , 0.1);//2 0 0.1
    liner_velocity_pid.set_error_tol(1);
    liner_position_pid.set_coefficient(2.6 , 0.006 , 0);//2.5 0.01 0
    liner_position_pid.set_error_tol(30);

    angular_velocity_pid.set_coefficient(10 , 0 , 0.5);//10 0 0
    angular_velocity_pid.set_error_tol(1);
    angular_position_pid.set_coefficient(20 , 0, 20);//20 0.005 0.005
    angular_position_pid.set_error_tol(5);

    route_timer.clear();

    if(cpt->isAutonomous()){
        turn_right_to(100 , 90);
    }
    cout<<route_timer.time(sec)<<endl<<endl;
}

void AUTOchassis::run_auto_route(void* p){
    competition* cpt = (competition*)p;

    liner_velocity_pid.set_coefficient(2, 0 , 0.1);
    liner_velocity_pid.set_error_tol(1);
    liner_position_pid.set_coefficient(2.5 , 0.01 , 0);
    liner_position_pid.set_error_tol(30);

    angular_velocity_pid.set_coefficient(10 , 0 , 0);
    angular_velocity_pid.set_error_tol(1);
    angular_position_pid.set_coefficient(20 , 0.005 , 0.005);
    angular_position_pid.set_error_tol(2);

    if(cpt->isAutonomous()){
        AUTOchassis::getInstance()->route();
    }
}

void AUTOchassis::run_skill_route(void* p){
    competition* cpt = (competition*)p;

    liner_velocity_pid.set_coefficient(2, 0 , 0.1);
    liner_velocity_pid.set_error_tol(1);
    liner_position_pid.set_coefficient(2.5 , 0.01 , 0);
    liner_position_pid.set_error_tol(30);

    angular_velocity_pid.set_coefficient(10 , 0 , 0);
    angular_velocity_pid.set_error_tol(1);
    angular_position_pid.set_coefficient(20 , 0.005 , 0.005);
    angular_position_pid.set_error_tol(2);

    if(cpt->isAutonomous()){
        AUTOchassis::getInstance()->skill_route();
    }
}