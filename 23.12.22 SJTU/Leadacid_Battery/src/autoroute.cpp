#include "autoroute.h"
using namespace vex;

void PlanA(competition *cpt){
    ChassisAuto autobase;
    //PID setting
    autobase.Line.setCoefficient(100,0.01,2.5);
    autobase.Line.seterrorTol(0.5);
    autobase.Line.setIrange(0.01,1);

    autobase.Angle.setCoefficient(390,8.9,2230);
    autobase.Angle.set_variable_param(500,0.07);
    autobase.Angle.seterrorTol(0.3);
    autobase.Angle.setIrange(0.01,2000);

    autobase.VisionX.setCoefficient(390,8.9,2230);
    autobase.VisionX.set_variable_param(500,0.07);
    autobase.VisionX.seterrorTol(0.3);
    autobase.VisionX.setIrange(0.01,1000);

    autobase.VisionY.setCoefficient(0.01,0,2.5);
    autobase.VisionY.seterrorTol(0.5);
    autobase.VisionY.setIrange(0.01,1);

    thread take(_auto_take,cpt);
    thread piston(_auto_piston,cpt);

    //actions

    //推车前两球得分
    TAKEIN_SWITCH=true;
    auto_movement(autobase,STRIGHT,-20,0,0,5,false);
    TAKEIN_SWITCH=false;
    auto_movement(autobase,STRIGHT,-20,0,0,5,false);
    auto_movement(autobase,LEFT,0,0,20,0.2);
    auto_movement(autobase,STRIGHT,-80,0,0,1.4);
    auto_movement(autobase,LEFT,0,0,70,0.25);
    auto_movement(autobase,STRIGHT,-100,0,0,1,false);
    wait(200,msec);
    auto_movement(autobase,STRIGHT,70,0,0,1);
    auto_movement(autobase,STRIGHT,-100,0,0,1,false);

    //拿球
    auto_movement(autobase,STRIGHT,50,0,0,0.5);
    auto_movement(autobase,RIGHT,0,0,90,0.35);
    auto_movement(autobase,STRIGHT,-50,0,0,0.8,false);
    auto_movement(autobase,STRIGHT,70,0,0,2);
    auto_movement(autobase,RIGHT,0,0,45,0.2);
    TAKEIN_SWITCH=true;
    auto_movement(autobase,STRIGHT,40,0,0,2,false);
    auto_movement(autobase,RIGHT,0,0,140,0.6);
    TAKEIN_SWITCH=false;TAKEOUT_SWITCH=true;
    auto_movement(autobase,STRIGHT,100,0,0,1.5,false);
    wait(20,msec);
    TAKEOUT_SWITCH=false;
    auto_movement(autobase,STRIGHT,-50,0,0,0.5);
    auto_movement(autobase,RIGHT,0,0,140,0.6);
    TAKEIN_SWITCH=true;
    auto_movement(autobase,STRIGHT,50,0,0,1.3,false);
    auto_movement(autobase,LEFT,0,0,140,0.6);
    auto_movement(autobase,STRIGHT,-50,0,0,1.5);
    auto_movement(autobase,LEFT,0,0,140,0.6);
    TAKEIN_SWITCH=false;TAKEOUT_SWITCH=true;
    auto_movement(autobase,STRIGHT,100,0,0,0.5,false);
    wait(20,msec);
    TAKEOUT_SWITCH=false;
}

void _auto_take(void* arg){
    competition* a=(competition*)arg;
    auto_take(a);
}

void _auto_piston(void* arg){
    competition* a=(competition*)arg;
    auto_piston(a);
}