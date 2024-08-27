#include "autoroute.h"
using namespace vex;

void PlanA(competition* cpt){
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
    thread arm(_auto_arm,cpt);
    thread shoot(_auto_shoot,cpt);
    thread piston(_auto_piston,cpt);
    
    //actions
    //打预装
    ARMDOWN_SWITCH=true;
    auto_movement(autobase,STRIGHT,-90,0,0,0.9);
    SHOOT_SWITCH=true;waitUntil(!SHOOT_SWITCH);
    ARMUP_SWITCH=true;

    //推中四
    auto_movement(autobase,LEFT,0,0,79,0.3);
    auto_movement(autobase,STRIGHT,-60,0,0,1);
    PISTONA_SWITCH=true;PISTONB_SWITCH=true;
    auto_movement(autobase,STRIGHT,-60,0,0,0.9);
    auto_movement(autobase,RIGHT,0,0,79,0.3);
    
    auto_movement(autobase,STRIGHT,60,0,0,0.4);
    auto_movement(autobase,STRIGHT,-100,0,0,0.8,false);
    
    auto_movement(autobase,STRIGHT,60,0,0,0.4);
    auto_movement(autobase,STRIGHT,-100,0,0,0.4,false);

    PISTONA_SWITCH=false,PISTONB_SWITCH=false;
    auto_movement(autobase,STRIGHT,50,0,0,0.5);
    auto_movement(autobase,LEFT,0,0,62,0.2);

    //回预装区打联队
    //BACK=true;
    //auto_movement(autobase,STRIGHT,100,0,0,2.3);
    /*TAKEIN_SWITCH=true;
    ARMDOWN_SWITCH=true;waitUntil(!ARMDOWN_SWITCH);
    wait(600,msec);
    ARMUP_SWITCH=true;waitUntil(!ARMDOWN_SWITCH);
    wait(600,msec);

    auto_movement(autobase,STRIGHT,-100,0,0,2.3);
    auto_movement(autobase,RIGHT,0,0,65,0.2);
    TAKEIN_SWITCH=false;
    wait(20,msec);
    TAKEOUT_SWITCH=true;
    auto_movement(autobase,STRIGHT,90,0,0,1.4);
    auto_movement(autobase,STRIGHT,-90,0,0,1.2);
    TAKEOUT_SWITCH=false;
    auto_movement(autobase,LEFT,0,0,50,0.2);
    RESET=true;*/

    //场外预装
    auto_movement(autobase,STRIGHT,100,0,0,2.3);
    TAKEIN_SWITCH=true;
    repeat(5){
        ARMDOWN_SWITCH=true;waitUntil(!ARMDOWN_SWITCH);
        wait(400,msec);
        ARMUP_SWITCH=true;waitUntil(!ARMDOWN_SWITCH);
        wait(600,msec);
        auto_movement(autobase,STRIGHT,-50,0,0,0.5);
        auto_movement(autobase,RIGHT,0,0,50,0.2);
        ARMDOWN_SWITCH=true;waitUntil(!ARMDOWN_SWITCH);
        wait(90,msec);
        SHOOT_SWITCH=true;waitUntil(!SHOOT_SWITCH);
        wait(90,msec);
        ARMUP_SWITCH=true;waitUntil(!ARMDOWN_SWITCH);
        wait(90,msec);
        auto_movement(autobase,LEFT,0,0,60,0.2);
        auto_movement(autobase,STRIGHT,50,0,0,0.5);
        wait(UPDATETIME,msec);
    }
    TAKEIN_SWITCH=false;
    TAKEIN_SWITCH = false;
    TAKEOUT_SWITCH = false;
    ARMUP_SWITCH = false;
    ARMDOWN_SWITCH = false;
    SHOOT_SWITCH = false;
    PISTONA_SWITCH = false;
    PISTONB_SWITCH = false;
    BACK = false;RESET = false;

    wait(100,msec);

    take.interrupt();arm.interrupt();
    piston.interrupt();shoot.interrupt();

}

void _auto_arm(void* arg){
    competition* a=(competition*)arg;
    auto_arm(a);
}

void _auto_shoot(void* arg){
    competition* a=(competition*)arg;
    auto_shoot(a);
}

void _auto_take(void* arg){
    competition* a=(competition*)arg;
    auto_take(a);
}

void _auto_piston(void* arg){
    competition* a=(competition*)arg;
    auto_piston(a);
}