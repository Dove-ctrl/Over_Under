#ifndef BASICFUNCTION_H_
#define BASICFUNCTION_H_

#include "vex.h"
using namespace vex;

void move(int,int);//input right motors' vel and left motors' vel
void take_roller(int);//take in the plate or get the roller, input power
void shoot(double,int);//input rotation and power
#endif