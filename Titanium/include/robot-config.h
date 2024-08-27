#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_

using namespace vex;
using namespace std;

/* 功能选择 */
#define DEBUG 0 
#define COMPETITION 1
#define SKILL 2

extern const int MAXVOLTAGE;
extern const int UPDATETIME;

extern brain Brain;

extern controller Controller1;

extern motor LF;
extern motor LB;
extern motor LMF;
extern motor LMB;
extern motor RF;
extern motor RB;
extern motor RMF;
extern motor RMB;

extern motor Takein;

extern motor Lshoot;
extern motor Rshoot;

#endif