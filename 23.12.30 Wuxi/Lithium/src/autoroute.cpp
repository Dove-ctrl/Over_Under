#include "autoroute.h"

void PlanA(competition* arg){
    AUTOchassis base;
    base.reset_sensor(AUTOchassis::sensor::INERTIAL);

    //PID setting
    base.LinerPID.setCoefficient(2,0.001,3.2);
    base.LinerPID.seterrorTol(0.5);
    base.LinerPID.setIrange(0.01,1500);
    base.LinerPID.setMaxtime(3000);

    base.AngularPID.setCoefficient(150,1,250);
    base.AngularPID.set_variable_param(500,0.07);
    base.AngularPID.seterrorTol(0.3);
    base.AngularPID.setIrange(0.01,1000);
    base.AngularPID.setMaxtime(1500);

}

void debug(competition* arg){
    AUTOchassis base;

    Spread.setVelocity(100,pct);

    base.reset_sensor(AUTOchassis::sensor::INERTIAL);

    //PID setting
    base.LinerPID.setCoefficient(2,0.001,3.2);
    base.LinerPID.seterrorTol(0.5);
    base.LinerPID.setIrange(0.01,1500);
    base.LinerPID.setMaxtime(10000);

    base.AngularPID.setCoefficient(116,1,300);
    base.AngularPID.set_variable_param(500,0.07);
    base.AngularPID.seterrorTol(1.0);
    base.AngularPID.setIrange(0.01,1500);
    base.AngularPID.setMaxtime(2000);

    wait(2000,msec);
    /*base.autochassis_movement(40,1.5,true,STRIGHT);
    Spread.spinFor(fwd,380,msec);
    base.autochassis_movement(20,0.2,true,STRIGHT);
    base.autochassis_movement(6.5,93,TURN);
    Spread.spinFor(reverse,450,msec);
    base.autochassis_movement(83,0.8,false,STRIGHT);
    base.autochassis_movement(-30,0.5,true,STRIGHT);
    base.autochassis_movement(83,0.8,false,STRIGHT);
    base.autochassis_movement(-30,0.3,true,STRIGHT);
    wait(500,msec);
    base.autochassis_movement(-6.5,-46,TURN);
    base.autochassis_movement(-50,-2,true,STRIGHT);

    Spread.spinFor(fwd,380,msec);*/

    base.autochassis_movement(30,1,true,STRIGHT);
    base.autochassis_movement(6.5,45,TURN);
    wait(5000,msec);

    base.autochassis_movement(-30,-1.1,true,STRIGHT);

    Arm.setVelocity(35,pct);
    Spread.spinFor(fwd,380,msec);
    repeat(10){
        Arm.spinFor(fwd,890,msec);
        wait(400,msec);
        Arm.spinFor(reverse,890,msec);
    }
    wait(600,msec);
    Arm.spinFor(reverse,150,msec);
    base.autochassis_movement(6.5,60,TURN);
    base.autochassis_movement(50,1.6,true,STRIGHT);
    base.autochassis_movement(-30,-0.7,true,STRIGHT);
    Spread.spinFor(reverse,380,msec);

    Arm.spinFor(fwd,900,msec);
    base.autochassis_movement(50,3.7,true,STRIGHT);
    //base.autochassis_movement(-50,-1.8,false,STRIGHT);
    Arm.spinFor(reverse,900,msec);

    /*Arm.spinFor(reverse,900,msec);
    base.autochassis_movement(-6.5,-45,TURN);
    wait(200,msec);
    base.autochassis_movement(100,2.2,false,STRIGHT);
    wait(200,msec);
    base.autochassis_movement(-30,-0.3,true,STRIGHT);
    wait(500,msec);
    base.autochassis_movement(50,0.3,true,STRIGHT);
    wait(200,msec);
    base.autochassis_movement(-50,-0.3,true,STRIGHT);
    base.autochassis_movement(6.5,40,TURN);
    base.autochassis_movement(-50,-1.4,true,STRIGHT);
    base.autochassis_movement(6.5,40,TURN);
    Arm.spinFor(fwd,890,msec);
    wait(400,msec);
    base.autochassis_movement(-50,-1.6,true,STRIGHT);
    Arm.spinFor(fwd,890,msec);*/

    //测试用
    //base.autochassis_movement(50,3,true,STRIGHT);

    /*base.reset_sensor(base.ALLSENSOR);
    while (1)
    {
        LF.spinToPosition(3000,deg,100,velocityUnits::pct,false);
        RF.spinToPosition(3000,deg,100,velocityUnits::pct,false);
        LB.spinToPosition(3000,deg,100,velocityUnits::pct,false);
        RB.spinToPosition(3000,deg,100,velocityUnits::pct,false);
        LM.spinToPosition(3000,deg,100,velocityUnits::pct,false);
        RM.spinToPosition(3000,deg,100,velocityUnits::pct,false);
        wait(20,msec);
        if(base.get_current_position()>3000){break;}
    }*/
    
    //wait(50,msec);
    //base.autochassis_movement(-10,-90,TURN);


}