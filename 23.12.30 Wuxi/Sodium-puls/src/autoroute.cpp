#include "autoroute.h"

void PlanA(competition* arg){
    AUTOchassis base;
    Inertial.setHeading(180,deg);

    thread _piston_auto(auto_piston,&arg);
    thread _take_in(auto_take,&arg);

    piston_left=true;
    base.turn_right(75);
    wait(300,msec);
    base.forward(40,0.4);
    base.backward(40,0.3);
    piston_left=false;
    base.turn_left(150);
    base.backward(60,0.6);
    wait(500,msec);
    base.forward(40,0.3);
    wait(500,msec);
    base.backward(60,0.35);//最后一次后撞
    wait(500,msec);
    base.forward(40,0.3);
    base.turn_left(179);
    base.forward(40,1.2);
    base.turn_right(45);
    Inertial.setHeading(180,deg);
    wait(300,msec);
    base.backward(50,0.22);
    wait(100,msec);
    Inertial.setHeading(180,deg);
    wait(300,msec);
    base.forward(10,0.1);
    base.turn_right(75);
    take_in=true;
    base.forward(15,2.7);//携带中场球 到我方前场
    //base.backward(30,0.2);
    base.turn_right(10);
    base.turn_right(70);
    wait(500,msec);
    base.forward(18,1.3);//斜撞底墙
    wait(300,msec);
    base.turn_right(10);
    take_in=false;
    base.forward(20,0.65);//顶
    Inertial.setHeading(180,deg);
    wait(300,msec);
    base.backward(40,0.5);//后撞
    
    base.turn_right(20);
    base.backward(20,0.2);//波粽子
    piston_right=true;
    wait(500,msec);
    base.turn_left(30);
    base.forward(30,0.5);
    base.backward(40,0.3);
    piston_right=false;
    base.turn_left(170);
    base.backward(50,0.9);
    wait(300,msec);
    base.forward(15,0.2);
    wait(200,msec);
    base.backward(50,0.4);
    Inertial.setHeading(180,deg);
    wait(300,msec);
    base.forward(18,0.2);
    base.turn_right(90);
    base.backward(50,0.4);
    Inertial.setHeading(180,deg);
    wait(300,msec);//kaishixiqiu
    base.forward(50,1);
    base.turn_right(20);
    take_in=true;
    base.forward(28,1.1);
    base.backward(30,0.3);
    base.turn_right(120);
    take_in=false;take_out=true;
    base.forward(30,0.3);
    base.backward(30,0.3);
    take_out=false;take_in=true;
    base.turn_right(70);
    base.forward(10,1.7);
    base.turn_right(90);
    base.turn_right(160);
    wait(300,msec);
    base.backward(30,0.3);
    wait(300,msec);
    Inertial.setHeading(180,deg);
    wait(300,msec);
    piston_left=true;piston_right=true;
    take_in=false;take_out=true;
    base.forward(30,1.2);
    wait(300,msec);
    base.backward(30,1);
    wait(300,msec);
    base.turn_right(17);
    base.backward(50,1.2);
    wait(300,msec);
    Inertial.setHeading(180,deg);
    wait(300,msec);
    base.forward(30,1);
    wait(300,msec);
    base.backward(40,1.1);
    


}