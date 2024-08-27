#ifndef ROBOT_CONFIG_H_
#define ROBOT_CONFIG_H_

using namespace vex;

extern const int MAXVOLTAGE; 
extern const int UPDATETIME;

extern brain Brain;
extern controller Controller1;

extern motor Takein;

extern motor ArmL;
extern motor ArmR;

extern motor Shoot;

extern motor LF;
extern motor LB;
extern motor LU;
extern motor RF;
extern motor RB;
extern motor RU;

extern inertial INERTIAL;

extern digital_out piston1;
extern digital_out piston2;
extern digital_out piston3;

extern bumper Lbumper;
extern bumper Rbumper;

extern vision::signature Vision__S_GREEN;
extern vision::signature Vision__S_RED;
extern vision::signature Vision__S_BULE;

extern vision Vision;

#endif