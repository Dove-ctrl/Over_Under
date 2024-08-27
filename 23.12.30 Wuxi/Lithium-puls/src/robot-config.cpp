#include "vex.h"

using namespace vex;

const int UPDATETIME = 5;
const int MAXVOLTAGE = 12700;
const int LeftDEADZONE = 5;
const int RightDEADZONE = 5;



brain Brain;
controller Controller1;

motor LF = motor(PORT19,ratio6_1,true);
motor LB = motor(PORT2,ratio6_1,true);
motor LM = motor(PORT7,ratio6_1,false);
motor RF = motor(PORT15,ratio6_1,false);
motor RB = motor(PORT18,ratio6_1,false);
motor RM = motor(PORT16,ratio6_1,true);

motor Arm = motor(PORT4,ratio36_1,false);

motor Spread = motor(PORT20,ratio18_1,true);

motor Hang = motor(PORT1,ratio18_1,false);

inertial Inertial = inertial(PORT10);


