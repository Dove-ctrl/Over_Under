#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_

#define MAXVOLTAGE 12750
#define UPDATETIME 10

using namespace vex;

extern brain Brain;

extern controller Controller1;

extern motor lf;
extern motor rf;
extern motor lb;
extern motor rb;

extern inertial Inertial;

#endif