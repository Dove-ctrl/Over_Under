#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_

using namespace vex;

extern const int UPDATETIME;
extern const int MAXVOLTAGE;

extern brain Brain;
extern controller Controller1;

extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;
extern motor LM;
extern motor RM;

extern inertial Inertial;

#endif