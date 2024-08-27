#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_

#include "vex.h"
using namespace vex;

extern const int UPDATETIME;
extern const int MAXRPM;
extern const int MAXVOLTAGE;
extern const int MAXMOVETIME;
/* extern const int ANGLE; */
/* extern const float SCALINGRATIO; */
/* extern const float X0;
extern const float Y0; */

extern brain Brain;
extern controller Controller1;

extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor LMF;
extern motor LMB;
extern motor RMF;
extern motor RMB;

extern motor Takein;

extern motor Lhang;
extern motor Rhang;

extern inertial Inertial;

extern digital_out LFPiston;
extern digital_out RFPiston;
extern digital_out LBPiston;
extern digital_out RBPiston;

extern encoder Coder_left;
extern encoder Coder_right;

#endif