#ifndef AUTONOMOUS_H_
#define SUTONOMOUS_H_

#include "vex.h"
using namespace vex;

void runauton();
void movefwd(double,int);
void takein(double,int);
void turnleft(double,int);
void turnright(double,int);
void roller(double,int);
void resettriger(int);
void autoshoot(double,int);

#endif