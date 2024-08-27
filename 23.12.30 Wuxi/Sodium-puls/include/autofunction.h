#ifndef AUTOFUNCTION_H_
#define AUTOFUNCTION_H_

#include "vex.h"
#include "chassis.h"
using namespace vex;

extern bool take_in;
extern bool take_out;
extern bool piston_left;
extern bool piston_right;

void auto_take(void*);
void auto_piston(void*);

#endif