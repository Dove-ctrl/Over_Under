#include "opfunction.h"
using namespace vex;

const int LeftDEADZONE = 5;
const int RightDEADZONE = 5;

void op_movement(){
    Chassis base;
    while(true){
        base.get_controller(150,150);
        //deadzone setting
        if(abs(Controller1.Axis3.position())<=LeftDEADZONE && abs(Controller1.Axis1.position())<=RightDEADZONE){
            base.motor_brake(coast);
        }else{
            base.chassis_movement();
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void arm_control(){
    /*int bumperswitch;
    //determine the movement trend of the arm,if you press R1 means the channel of R1 is opening
    bool channelR1,channelR2;
    while(true){
        //separate two statuses of bumper to avoid the arm being stucked
        if(Lbumper.pressing()||Rbumper.pressing()){bumperswitch=1;}
        else{bumperswitch=0;}

        switch (bumperswitch)
        {
        case 0:
            if(Controller1.ButtonR1.pressing()){
                //if press R1,the arm move towards the direction that R1 controls,so the channelR1 is true
                ArmL.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
                ArmR.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
                channelR1=true,channelR2=false;
            }else if(Controller1.ButtonR2.pressing()){
                //if press R2,the arm move towards the direction that R2 controls,so the channelR2 is true
                ArmL.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
                ArmR.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
                channelR1=false,channelR2=true;
            }else{
                ArmL.stop(coast);
                ArmR.stop(coast);
            }
            break;
        case 1:
            if(channelR1){
                while(Lbumper.pressing()||Rbumper.pressing()){
                    ArmL.spin(reverse,(Controller1.ButtonR2.pressing())*MAXVOLTAGE,voltageUnits::mV);
                    ArmR.spin(reverse,(Controller1.ButtonR2.pressing())*MAXVOLTAGE,voltageUnits::mV);
                }
                break;
            }else if(channelR2){
                while(Lbumper.pressing()||Rbumper.pressing()){
                    ArmL.spin(fwd,(Controller1.ButtonR1.pressing())*MAXVOLTAGE,voltageUnits::mV);
                    ArmR.spin(fwd,(Controller1.ButtonR1.pressing())*MAXVOLTAGE,voltageUnits::mV);
                }
                break;
            }else{
                ArmL.spin(fwd,(Controller1.ButtonR1.pressing())*MAXVOLTAGE-(Controller1.ButtonR2.pressing())*MAXVOLTAGE,voltageUnits::mV);
                ArmR.spin(fwd,(Controller1.ButtonR1.pressing())*MAXVOLTAGE-(Controller1.ButtonR2.pressing())*MAXVOLTAGE,voltageUnits::mV);
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(UPDATETIME);
    }*/
    while(true){
        if(Controller1.ButtonR1.pressing())
        {
            ArmL.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
            ArmR.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
        }
        else if(Controller1.ButtonR2.pressing())
        {
            ArmL.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
            ArmR.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
        }else{
            ArmL.stop(brake);
            ArmR.stop(brake);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void takein_control(){
    while(true){
        if(Controller1.ButtonL1.pressing()){
            Takein.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
        }else if(Controller1.ButtonL2.pressing()){
            Takein.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
        }else{
            Takein.stop(brake);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void shoot_control(){
    Shoot.setVelocity(100,pct);
    while(true){
        if(Controller1.ButtonX.pressing()){
            Shoot.resetPosition();
            Shoot.spinTo(-1074,deg,true);
        }else if(Controller1.ButtonDown.pressing()){
            Shoot.spin(reverse,100,pct);
        }else if(Controller1.ButtonUp.pressing()){
            Shoot.spin(fwd,100,pct);
        }else{
            Shoot.stop(hold);
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void piston_control(){
    bool pa=false,pb=false,pc=false;
    while(true){
        if(Controller1.ButtonA.pressing()){
            if(!pa){pa=true;waitUntil(!Controller1.ButtonA.pressing());}
            else if(pa){pa=false;waitUntil(!Controller1.ButtonA.pressing());}
        }else if(Controller1.ButtonB.pressing()){
            if(!pb){pb=true;waitUntil(!Controller1.ButtonB.pressing());}
            else if(pb){pb=false;waitUntil(!Controller1.ButtonB.pressing());}
        }else if(Controller1.ButtonRight.pressing()){
            pc=true;
        }
        piston1.set(pa);
        piston2.set(pb);
        piston3.set(pc);
        this_thread::sleep_for(UPDATETIME);
    }
}