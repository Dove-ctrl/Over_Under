#include "basicfunction.h"

void move(int right,int left){//input right motors' vel and left motors' vel
    LF.spin(fwd,left,pct);
    LM.spin(fwd,left,pct);
    LB.spin(fwd,left,pct);
    RF.spin(fwd,right,pct);
    RM.spin(fwd,right,pct);
    RB.spin(fwd,right,pct);
    if(right==0 && left==0){
        LF.stop(brake);
        LM.stop(brake);
        LB.stop(brake);
        RF.stop(brake);
        RM.stop(brake);
        RB.stop(brake);
    }
}

void take_roller(int power){
    if(Controller1.ButtonR2.pressing()){
        Take.spin(fwd,power,pct);
    }else if(Controller1.ButtonR1.pressing()){
        Take.spin(reverse,power,pct);
    }else{
        Take.stop(hold);
    }
}

void shoot(double r,int power){
    if(Controller1.ButtonL1.pressing()){
        Fire.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    }
}