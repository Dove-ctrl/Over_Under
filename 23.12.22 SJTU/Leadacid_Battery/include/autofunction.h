#ifndef AUTOFUNCTION_H_
#define AUTOFUNCTION_H_

#include "vex.h"
#include "chassis.h"
#include "PID.h"
#include "vision.h"
using namespace vex;

const enum movetype{
    STRIGHT,LEFT,RIGHT
};

extern bool TAKEIN_SWITCH;
extern bool TAKEOUT_SWITCH;
extern bool PISTONA_SWITCH;
extern bool PISTONB_SWITCH;

void auto_movement(ChassisAuto,movetype,float,float,float,float);
void auto_movement(ChassisAuto,movetype,float,float,float,float,bool);
void auto_take(competition*);
void auto_piston(competition*);
bool vision_tracking(ChassisAuto,object,int,int,float);


#endif