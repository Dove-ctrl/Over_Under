#include "vex.h"

using namespace vex;

const int UPDATETIME = 5;
const int MAXVOLTAGE = 12700;
const int LeftDEADZONE = 5;
const int RightDEADZONE = 5;

brain Brain;
controller Controller1;

motor LF = motor(PORT19,ratio6_1,true);
motor LB = motor(PORT8,ratio6_1,true);
motor LM = motor(PORT3,ratio6_1,false);
motor RF = motor(PORT9,ratio6_1,false);
motor RB = motor(PORT1,ratio6_1,false);
motor RM = motor(PORT2,ratio6_1,true);

motor ArmL = motor(PORT12,ratio36_1,false);
motor ArmR = motor(PORT11,ratio36_1,true);

motor Takein = motor(PORT4,ratio36_1,true);

digital_out Piston_left = digital_out(Brain.ThreeWirePort.H);
digital_out Piston_right = digital_out(Brain.ThreeWirePort.G);
digital_out Piston_triger = digital_out(Brain.ThreeWirePort.A);

inertial Inertial = inertial(PORT20);