#ifndef VISION_H_
#define VISION_H_

#include "vex.h"
using object = vision::object;
using signature = vision::signature;

object get_triball(signature);
object get_goal(signature);

#endif