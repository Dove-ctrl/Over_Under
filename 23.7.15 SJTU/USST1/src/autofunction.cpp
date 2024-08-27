#include "autofunction.h"

void runauto(){
    movefwd(-0.04,8);
    wait(1000,msec);
    roller(1.5,100);
    wait(1000,msec);
    resettriger(4,90);
    movefwd(0.47,90);
    wait(300,msec);
    takein(25,100);
    autonbrake();
    wait(2000,msec);
    turnleft(14,10);
    open(0.6,90);
    wait(1800,msec);
    autoshoot(7,95);
    wait(500,msec);
    turnright(100,20);
    takein(40,100);
    movefwd(0.99,40);
    turnleft(45,10);
    movefwd(0.4,10);
    movefwd(-0.35,10);
    turnleft(115,10);
    movefwd(0.2,10);
    open(0.5,90);
    wait(1000,msec);
    autoshoot(7,95);
}

void movefwd(double length,int power){//move foward,distence depends on the rotation
    double c=3.88;
    double r=length*c;
    LF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB1.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB2.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB1.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB2.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void takein(double r,int power){//take in the object
    mainTake.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    Roller.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
}

void turnright(int degree,int power){//turn to special direction
    float c=0.01018252;
    double r=degree*(c);
    LF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB1.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB2.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RF.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB1.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB2.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void turnleft(int degree,int power){//turn to special direction
    double r;
    float c=0.01018252;
    r=degree*(c);
    LF.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB1.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB2.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB1.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB2.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void roller(double r,int power){//get the roller
    mainTake.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    Roller.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
}

void resettriger(double r,int power){//reset the triger position
    Fire.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
}

void autoshoot(double r,int power){//shoot
    Fire.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void open(double time,int power){//open plate
    Roller.spinFor(vex::directionType::fwd,time,vex::timeUnits::sec,power,vex::velocityUnits::pct);
}
void autonbrake(){
    LF.stop(brake);
    LB1.stop(brake);
    LB2.stop(brake);
    RF.stop(brake);
    RB1.stop(brake);
    RB2.stop(brake);
}