#include "vex.h"

using namespace vex;
using signature = vision::signature;

const int MAXVOLTAGE = 12700;
const int UPDATETIME = 10;

brain Brain;
controller Controller1 = controller(primary);

motor LF = motor(PORT3,ratio6_1,true);
motor LB = motor(PORT9,ratio6_1,true);
motor RF = motor(PORT13,ratio6_1,false);
motor RB = motor(PORT11,ratio6_1,false);
motor LM = motor(PORT2,ratio6_1,true);
motor RM = motor(PORT12,ratio6_1,false);

inertial INERTIAL = inertial(PORT6);

motor Takein = motor(PORT15,ratio18_1,true);

digital_out piston1 = digital_out(Brain.ThreeWirePort.A);
digital_out piston2 = digital_out(Brain.ThreeWirePort.H);
digital_out piston3 = digital_out(Brain.ThreeWirePort.B);

signature Vision__S_GREEN = signature (1, -4587, -3421, -4004, -4763, -3525, -4144, 3, 0);
signature Vision__S_RED = signature (2, 7927, 10923, 9425, -825, -421, -623, 3, 0);
signature Vision__S_BULE = signature (3, -3171, -2469, -2820, 7753, 9415, 8584, 3, 0);

vision Vision = vision (PORT5, 50, Vision__S_GREEN, Vision__S_RED, Vision__S_BULE);

void vexcodeInit(void) {
  
}