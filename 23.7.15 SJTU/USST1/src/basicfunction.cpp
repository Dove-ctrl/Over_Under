#include "basicfunction.h"

void basicmovment(float v3,float v1){
    int a=v3,b=v1;
    LF.spin(fwd,v3+v1,pct);
    LB1.spin(fwd,v3+v1,pct);
    LB2.spin(fwd,v3+v1,pct);
    RF.spin(fwd,v3-v1,pct);
    RB1.spin(fwd,v3-v1,pct);
    RB2.spin(fwd,v3-v1,pct);
    if(a==0&&b==0){
        LF.stop(brake);
        LB1.stop(brake);
        LB2.stop(brake);
        RF.stop(brake);
        RB1.stop(brake);
        RB2.stop(brake);
    }
}

void maintake(int power1,int power2){
    if(Controller1.ButtonR2.pressing()){//take in and roller
        mainTake.spin(forward,power1,pct);
        Roller.spin(forward,-power2,pct);
    }else if(Controller1.ButtonR1.pressing()){//take out
        mainTake.spin(forward,-power1,pct);
    }else if(Controller1.ButtonL2.pressing()){//open
        Roller.spin(forward,power2,pct);
    }else{
        mainTake.stop(hold);
        Roller.stop(hold);
    }
}

void shoot(int power,double r){
    if(Controller1.ButtonL1.pressing()){
        Fire.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    }
}

void usershoot(int power){
    if(Controller1.ButtonA.pressing()){
        Fire.spin(fwd,power,pct);
    }else{
        Fire.stop(hold);
    }
}

void reset(double r,int power){
    if(Controller1.ButtonY.pressing()){
        Fire.spinFor(vex::directionType::fwd,r,vex::rotationUnits::rev,power,vex::velocityUnits::pct,false);
    }
}