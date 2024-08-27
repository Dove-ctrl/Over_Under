#include "autofunction.h"

void AUTOchassis::autochassis_movement(float lv,float t_position,bool pid_switch,movetype = STRIGHT){
    reset_sensor(ALLSENSOR);
    lv=(lv/100)*MAXVOLTAGE;
    if(pid_switch){
        t_position=1527*t_position;
        set_basic_Linervel_Angularvel(lv,-150);
        //LinerPID.setTarget(t_position); 
        //AngularPID.setTarget(180-9.55);
        //LinerPID.resetTimer();
        AngularPID.resetTimer();
        do{
            position=get_current_position();
            yagon=Inertial.heading(deg);
            //get_revised_value(0,yagon);
            motor_group_movement();
            wait(UPDATETIME/2,msec);
        }while(fabs(position)<=fabs(t_position));
        motor_group_stop(brake);
        reset_sensor(VELOCITY);
        //LinerPID.resetfirstTime();LinerPID.resetI();LinerPID.resetoutput();LinerPID.resetTimer();
        //AngularPID.resetfirstTime();AngularPID.resetI();AngularPID.resetoutput();AngularPID.resetTimer();
        wait(50,msec);
    }else{
        t_position=1527*t_position;
        set_basic_Linervel_Angularvel(lv,0);
        do{
            position=get_current_position();
            motor_group_movement();
            wait(UPDATETIME/2,msec);
        }while(fabs(position)<=fabs(t_position));
        motor_group_stop(brake);
        reset_sensor(VELOCITY);
        wait(50,msec);
    }    
}

void AUTOchassis::autochassis_movement(float av,float t_yagon,movetype = TURN){
    reset_sensor(ALLSENSOR);
    av=(av/100)*MAXVOLTAGE;
    t_yagon=t_yagon+180;
    set_basic_Linervel_Angularvel(0,av);
    AngularPID.setTarget(t_yagon);AngularPID.resetTimer();
    timer Tout ;Tout.clear();
    do{
        yagon=Inertial.heading(deg);
        get_revised_value(0,yagon);
        motor_group_movement();
        wait(UPDATETIME,msec);
        if(fabs(Inertial.gyroRate(axisType::xaxis,dps))<0.1 && Tout.time(msec)>800){break;}
    }while(!AngularPID.targetArrived());
    motor_group_stop(brake);
    AngularPID.resetfirstTime();AngularPID.resetI();AngularPID.resetoutput();AngularPID.resetTimer();
    wait(50,msec);
}

void AUTOchassis::turn_around(float velocity){
    int _heading=Inertial.heading();
    Inertial.setHeading(90,deg);
    set_basic_Linervel_Angularvel(0,velocity);
    timer Tout_ ;Tout_.clear();
    AngularPID.setTarget(270);AngularPID.resetTimer();
    do{
        yagon=Inertial.heading(deg);
        get_revised_value(0,yagon);
        motor_group_movement();
        wait(UPDATETIME/2,msec);
        if(fabs(Inertial.gyroRate(axisType::xaxis,velocityUnits::dps))<0.01 && Tout_.time(msec)>1000){break;}
    }while(!AngularPID.targetArrived());
    motor_group_stop(brake);
    AngularPID.resetfirstTime();AngularPID.resetI();AngularPID.resetoutput();AngularPID.resetTimer();
    Inertial.setHeading(_heading,deg);
}