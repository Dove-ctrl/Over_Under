#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_

using namespace vex;

extern const int UPDATETIME;
extern const int MAXVOLTAGE; 
extern const int LeftDEADZONE;
extern const int RightDEADZONE;

extern brain Brain;
extern controller Controller1;

extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor LM;
extern motor RM;

extern motor Arm;

extern motor Spread;

extern motor Hang;

extern inertial Inertial;


#endif
