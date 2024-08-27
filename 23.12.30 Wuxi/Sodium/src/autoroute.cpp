#include "autoroute.h"

void PlanA(competition* arg){
    AUTOchassis base;
    base.reset_sensor(AUTOchassis::sensor::INERTIAL);

    //PID setting
    base.LinerPID.setCoefficient(2,0.001,3.2);
    base.LinerPID.seterrorTol(0.5);
    base.LinerPID.setIrange(0.01,1500);
    base.LinerPID.setMaxtime(3000);

    base.AngularPID.setCoefficient(116,0,300);
    base.AngularPID.set_variable_param(500,0.07);
    base.AngularPID.seterrorTol(1);
    base.AngularPID.setIrange(0.01,1000);
    base.AngularPID.setMaxtime(1500);

}

void debug(competition* arg){
    AUTOchassis base;
    thread autopiston(auto_piston,&arg);
    thread autotake(auto_take,&arg);

    base.reset_sensor(AUTOchassis::sensor::INERTIAL);

    //PID setting
    base.LinerPID.setCoefficient(2,0.001,3.2);
    base.LinerPID.seterrorTol(0.5);
    base.LinerPID.setIrange(0.01,1500);
    base.LinerPID.setMaxtime(10000);

    base.AngularPID.setCoefficient(116,0,254);
    base.AngularPID.set_variable_param(500,0.07);
    base.AngularPID.seterrorTol(0.3);
    base.AngularPID.setIrange(0.01,1500);
    base.AngularPID.setMaxtime(2000);

    //近联队
    //base.autochassis_movement(20,45,TURN);
    //base.autochassis_movement(80,1,false,STRIGHT);


    piston_right=true;
    base.autochassis_movement(10.5,75,TURN);
    base.autochassis_movement(-80,0.8,false,STRIGHT);
    wait(300,msec);
    base.autochassis_movement(50,0.3,false,STRIGHT);
    wait(200,msec);
    base.autochassis_movement(-70,-0.35,false,STRIGHT);

    piston_right=false;
    base.autochassis_movement(50,0.3,false,STRIGHT);
    wait(200,msec);
    base.autochassis_movement(-70,-0.35,false,STRIGHT);

    //base.autochassis_movement(50,0.3,false,STRIGHT);

    //去中场
    /*base.autochassis_movement(-6.5,-45,TURN);
    base.autochassis_movement(50,0.85,false,STRIGHT);
    base.autochassis_movement(-6.5,-55,TURN);

    //吸中场球
    take_in=true;
    base.autochassis_movement(50,3.2,false,STRIGHT);

    //塞中场球
    base.autochassis_movement(-6.5,-45,TURN);
    base.autochassis_movement(50,1.2,false,STRIGHT);
    base.autochassis_movement(-6.5,-48,TURN);
    base.autochassis_movement(70,0.3,false,STRIGHT);


    //远联队
    base.autochassis_movement(-40,-0.33,false,STRIGHT);
    base.autochassis_movement(3.5,30,TURN);
    base.autochassis_movement(-40,-0.33,false,STRIGHT);
    base.autochassis_movement(3.5,30,TURN);
    piston_right=true;
    wait(200,msec);
    base.autochassis_movement(-6.5,-60,TURN);
    base.autochassis_movement(50,0.4,false,STRIGHT);
    base.autochassis_movement(-35,-0.3,false,STRIGHT);
    piston_right=false;
    base.autochassis_movement(-13,-150,TURN);
    wait(200,msec);
    piston_right=true;
    base.autochassis_movement(-90,-0.8,false,STRIGHT);
    base.autochassis_movement(50,0.3,false,STRIGHT);
    base.autochassis_movement(-90,-0.4,false,STRIGHT);
    piston_right=false;
    wait(500,msec);
    base.autochassis_movement(50,0.2,false,STRIGHT);

    //怼墙
    base.reset_sensor(base.ALLSENSOR);
    int d=-590;
    base.reset_sensor(base.VELOCITY);
    LF.spinToPosition(-d,deg,30,velocityUnits::pct,false);
    RF.spinToPosition(d,deg,30,velocityUnits::pct,false);
    LB.spinToPosition(-d,deg,30,velocityUnits::pct,false);
    RB.spinToPosition(d,deg,30,velocityUnits::pct,false);
    LM.spinToPosition(-d,deg,30,velocityUnits::pct,false);
    RM.spinToPosition(d,deg,30,velocityUnits::pct,true);
    wait(200,msec);

    base.autochassis_movement(-50,-0.29,false,STRIGHT);
    
    //3
    base.autochassis_movement(60,1.6,false,STRIGHT);//前进拿粽子1
    base.autochassis_movement(6.5,30,TURN);//对准1
    take_in=true;
    base.autochassis_movement(40,1,false,STRIGHT);
    base.autochassis_movement(-40,-0.4,false,STRIGHT);
    base.autochassis_movement(6.5,130,TURN);
    take_in=false;take_out=true;
    base.autochassis_movement(50,0.5,false,STRIGHT);
    base.autochassis_movement(-40,-0.3,false,STRIGHT);
    take_out=false;take_in=true;
    base.autochassis_movement(-6.5,-130,TURN);
    base.autochassis_movement(40,0.7,false,STRIGHT);
    base.autochassis_movement(-40,-0.4,false,STRIGHT);
    piston_left=true;
    base.autochassis_movement(6.5,160,TURN);
    base.autochassis_movement(-30,-0.5,false,STRIGHT);
    take_in=false;
    base.autochassis_movement(80,1.6,false,STRIGHT);
    base.autochassis_movement(-50,-1.2,false,STRIGHT);
    base.autochassis_movement(-6.5,-150,TURN);
    wait(300,msec);
    base.autochassis_movement(-6.5,-30,TURN);
    piston_right=true;
    base.autochassis_movement(-80,-1.3,false,STRIGHT);
    base.autochassis_movement(50,0.3,false,STRIGHT);
    wait(300,msec);
    base.autochassis_movement(-80,-0.28,false,STRIGHT);
    piston_left=false;piston_right=true;
    base.autochassis_movement(-6.5,-75,TURN);
    base.autochassis_movement(50,1.8,false,STRIGHT);*/
    
    
    autopiston.interrupt();autotake.interrupt();
}