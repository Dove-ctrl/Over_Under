#include "vex.h"

using namespace vex;
using signature = vision::signature;

const int MAXVOLTAGE = 12700;
const int UPDATETIME = 10;

brain Brain;
controller Controller1 = controller(primary);

motor Takein = motor(PORT1,ratio18_1,true);

motor ArmL = motor(PORT19,ratio36_1,true);
motor ArmR = motor(PORT15,ratio36_1,false);

motor Shoot = motor(PORT17,ratio36_1,false);

motor LF = motor(PORT7,ratio6_1,true);
motor LB = motor(PORT20,ratio6_1,true);
motor LU = motor(PORT18,ratio6_1,true);
motor RF = motor(PORT8,ratio6_1,false);
motor RB = motor(PORT14,ratio6_1,false);
motor RU = motor(PORT13,ratio6_1,false);

inertial INERTIAL = inertial(PORT16);

digital_out piston1 = digital_out(Brain.ThreeWirePort.A);
digital_out piston2 = digital_out(Brain.ThreeWirePort.B);
digital_out piston3 = digital_out(Brain.ThreeWirePort.E);

bumper Lbumper = bumper(Brain.ThreeWirePort.D);
bumper Rbumper = bumper(Brain.ThreeWirePort.C);

signature Vision__S_GREEN = signature (1, -4659, -3893, -4276, -4405, -3265, -3835, 2.5, 0);
signature Vision__S_RED = signature (2, 7485, 8875, 8180, -1199, -477, -838, 4.9, 0);
signature Vision__S_BULE = signature (3, -2541, -2009, -2276, 8015, 9175, 8594, 3, 0);

vision Vision = vision (PORT5, 50, Vision__S_GREEN, Vision__S_RED, Vision__S_BULE);