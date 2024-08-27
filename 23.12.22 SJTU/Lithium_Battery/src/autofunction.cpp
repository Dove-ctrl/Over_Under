#include "autofunction.h"
using namespace vex;

bool TAKEIN_SWITCH = false;
bool TAKEOUT_SWITCH = false;
bool ARMUP_SWITCH = false;
bool ARMDOWN_SWITCH = false;
bool SHOOT_SWITCH = false;
bool PISTONA_SWITCH = false;
bool PISTONB_SWITCH = false;
bool BACK = false;bool RESET = false;

/// @brief Using liner velocity and angular velocity to control chassis.
/// @param base instantiation of ChassisAuto
/// @param status move type:left, right, stright
/// @param LV liner velocity (pct)
/// @param AV angular velocity (pct)
/// @param yagon the yagon that be set by progarmmer
/// @param t when go stright,the time is used for keep moving,but when turn left or right,the time is used for stopping PID
void auto_movement(ChassisAuto base,movetype status,float LV,float AV,float yagon,float t){
    base.reset(base._ALLSENSOR);
    LV=(LV/100)*12700;AV=(AV/100)*12700;
    base.set_LinerVel_AngularVel(LV,AV);
    int _lv=LV;double k=-(_lv/(t*1000));
    switch (status)
    {
    case LEFT:
        INERTIAL.setHeading(180,deg);
        yagon=180-yagon;
        base.Angle.setTarget(yagon);
        base.reset(ChassisAuto::sensor::_TIMER);
        while(!base.Angle.targetArrived()){
            base.Angle.update(INERTIAL.heading());
            base.get_revised_value(0,base.Angle.getoutput());
            base.chassis_movement();
            if(base.T.value()>=t){break;}
            wait(UPDATETIME,msec);
        }
        base.reset(ChassisAuto::sensor::_MOTOR);
        base.Angle.resetfirstTime();base.Angle.resetI();base.Angle.resetoutput();
        wait(100,msec);
        break;
    case RIGHT:
        INERTIAL.setHeading(180,deg);
        yagon=180+yagon;
        base.Angle.setTarget(yagon);
        base.reset(ChassisAuto::sensor::_TIMER);
        while(!base.Angle.targetArrived()){
            base.Angle.update(INERTIAL.heading());
            base.get_revised_value(0,base.Angle.getoutput());
            base.chassis_movement();
            if(base.T.value()>=t){break;}
            wait(UPDATETIME,msec);
        }
        base.reset(ChassisAuto::sensor::_MOTOR);
        base.Angle.resetfirstTime();base.Angle.resetI();base.Angle.resetoutput();
        wait(100,msec);
        break;
    case STRIGHT:
        yagon=yagon+180;
        INERTIAL.setHeading(180,deg);
        base.Line.setTarget(yagon);
        base.reset(ChassisAuto::sensor::_TIMER);
        while(t>=base.T.value()){
            base.set_LinerVel_AngularVel(k*(base.T.time(msec))+_lv,0);
            base.Line.update(INERTIAL.heading());
            base.get_revised_value(0,base.Line.getoutput());
            base.chassis_movement();
            wait(UPDATETIME,msec);
        }
        base.reset(ChassisAuto::sensor::_MOTOR);
        base.Line.resetfirstTime();base.Line.resetI();base.Line.resetoutput();
        wait(100,msec);
        break;
    default:
        break;
    }
}

void auto_movement(ChassisAuto base,movetype = STRIGHT,float LV=0,float AV=0,float yagon=0,float t=0,bool smooth_mode = false){
    base.reset(base._ALLSENSOR);
    LV=(LV/100)*12700;AV=(AV/100)*12700;
    base.set_LinerVel_AngularVel(LV,AV);
    yagon=yagon+180;
    INERTIAL.setHeading(180,deg);
    base.Line.setTarget(yagon);
    base.reset(ChassisAuto::sensor::_TIMER);
    while(t>=base.T.value()){
        base.set_LinerVel_AngularVel(LV,0);
        base.Line.update(INERTIAL.heading());
        base.get_revised_value(0,base.Line.getoutput());
        base.chassis_movement();
        wait(UPDATETIME,msec);
    }
    base.reset(ChassisAuto::sensor::_MOTOR);
    base.Line.resetfirstTime();base.Line.resetI();base.Line.resetoutput();
    wait(100,msec);
}

void auto_take(competition* c){
    while(c->isAutonomous()){
        if(TAKEIN_SWITCH){
            Takein.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
        }
        else if(TAKEOUT_SWITCH){
            Takein.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
        }
        else{
            Takein.stop();
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void auto_arm(competition* c){
    int bumperswitch;
    bool channelDown=false,channelUp=true;
    while(c->isAutonomous()){
        //separate two statuses of bumper to avoid the arm being stucked
        if(Lbumper.pressing()||Rbumper.pressing()){bumperswitch=1;}
        else{bumperswitch=0;}

        switch (bumperswitch)
        {
        case 0:
            if(ARMDOWN_SWITCH){
                ArmL.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
                ArmR.spin(fwd,MAXVOLTAGE,voltageUnits::mV);
                channelDown=true,channelUp=false;
            }else if(ARMUP_SWITCH){
                ArmL.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
                ArmR.spin(reverse,MAXVOLTAGE,voltageUnits::mV);
                channelDown=false,channelUp=true;
            }else{
                ArmL.stop();
                ArmR.stop();
            }
            break;
        case 1:
            if(channelDown){
                ARMDOWN_SWITCH=false;
                while(Lbumper.pressing()||Rbumper.pressing()){
                    ArmL.spin(reverse,(ARMUP_SWITCH)*MAXVOLTAGE,voltageUnits::mV);
                    ArmR.spin(reverse,(ARMUP_SWITCH)*MAXVOLTAGE,voltageUnits::mV);
                }
                break;
            }else if(channelUp){
                ARMUP_SWITCH=false;
                while(Lbumper.pressing()||Rbumper.pressing()){
                    ArmL.spin(fwd,(ARMDOWN_SWITCH)*MAXVOLTAGE,voltageUnits::mV);
                    ArmR.spin(fwd,(ARMDOWN_SWITCH)*MAXVOLTAGE,voltageUnits::mV);
                }
                break;
            }else{
                ArmL.stop();
                ArmR.stop();
            }
            break;
        default:
            break;
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void auto_shoot(competition* c){
    Shoot.setVelocity(100,pct);
    double r=-1074.0;
    while(c->isAutonomous()){
        if(SHOOT_SWITCH){
            Shoot.resetPosition();
            Shoot.spinTo(r,deg,true);
            SHOOT_SWITCH=false;
        }else{
            if(BACK){
                Shoot.resetPosition();
                Shoot.spinTo(100.0,degrees,true);
                BACK=false;
            }else if(RESET){
                Shoot.resetPosition();
                Shoot.spinTo(-100.0,degrees,true);
                RESET=false;
            }else{Shoot.stop(brake);}
        }
        this_thread::sleep_for(UPDATETIME);
    }
}

void auto_piston(competition* c){
    while(c->isAutonomous()){
        piston1.set(PISTONA_SWITCH);
        piston2.set(PISTONB_SWITCH);
        this_thread::sleep_for(UPDATETIME);
    }
}

bool vision_tracking(ChassisAuto base,object sample,int targetX,int targetY,float t){
    timer T;T.clear();
    base.VisionX.setTarget(targetX);
    base.VisionY.setTarget(targetY);
    base.set_LinerVel_AngularVel(0,0);
    while(true){
        sample=get_triball(Vision__S_GREEN);
        base.VisionX.update(sample.centerX);
        base.VisionY.update(sample.centerY);

        base.get_revised_value(base.VisionY.getoutput(),base.VisionX.getoutput());
        base.chassis_movement();

        if((base.VisionX.targetArrived()&&base.VisionY.targetArrived())||T.value()>=t){
            base.VisionY.resetfirstTime();
            base.VisionY.resetI();
            base.VisionY.resetoutput();
            base.VisionX.resetfirstTime();
            base.VisionX.resetI();
            base.VisionX.resetoutput();
            return true;
            break;
        }
        return false;
        wait(UPDATETIME,msec);
    }
}

void auto_thread_stop(){
    

}