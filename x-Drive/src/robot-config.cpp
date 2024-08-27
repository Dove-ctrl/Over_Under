#include "vex.h"

using namespace vex;

brain Brain;
controller Controller1 = controller(primary);

motor lf = motor(PORT3,ratio18_1,false);
motor rf = motor(PORT1,ratio18_1,false);
motor lb = motor(PORT4,ratio18_1,false);
motor rb = motor(PORT2,ratio18_1,false);

inertial Inertial = inertial(PORT6);