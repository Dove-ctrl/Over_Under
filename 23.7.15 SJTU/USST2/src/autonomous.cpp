#include "autonomous.h"
void runauton(){
    resettriger(100);
}

void movefwd(double length,int power){
    double c=3.88;
    double r=length*c;
    LF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LM.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RM.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void takein(double r,int power){//take in the object
    Take.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
}
void turnleft(int degree,int power){
    float c=0.01018252;
    double r=degree*(c);
    LF.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LM.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RM.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void turnright(int degree,int power){//turn to special direction
    float c=0.01018252;
    double r=degree*(c);
    LF.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LM.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    LB.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RF.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RM.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    RB.spinFor(vex::directionType::rev,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,true);
}

void roller(double r=0.45,int power){
    Take.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
}

void resettriger(int power){
    double r=6.528;
    Fire.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
}