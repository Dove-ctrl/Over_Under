#include "vex.h"

using namespace vex;

const int UPDATETIME = 5;
const int MAXRPM = 650;
const int MAXVOLTAGE = 12750;
const int MAXMOVETIME = 2000;
/* const int ANGLE = 315; */
/* const float SCALINGRATIO = 8.64197; */
/* const float X0 = -20.0;
const float Y0 = 10.0; */

brain Brain;
controller Controller1 = controller(primary);

motor LF = motor(PORT16,ratio6_1,true);
motor LB = motor(PORT10,ratio6_1,true);
motor LMF = motor(PORT5,ratio6_1,false);
motor LMB = motor(PORT19,ratio6_1,false);
motor RF = motor(PORT6,ratio6_1,false);
motor RB = motor(PORT7,ratio6_1,false);
motor RMF = motor(PORT8,ratio6_1,true);
motor RMB = motor(PORT9,ratio6_1,true);

motor Takein = motor(PORT20,ratio18_1,false);

motor Lhang = motor(PORT1,ratio18_1,false);
motor Rhang = motor(PORT2,ratio18_1,true);

inertial Inertial = inertial(PORT17);

digital_out LFPiston = digital_out(Brain.ThreeWirePort.A);
digital_out RFPiston = digital_out(Brain.ThreeWirePort.D);
digital_out LBPiston = digital_out(Brain.ThreeWirePort.B);
digital_out RBPiston = digital_out(Brain.ThreeWirePort.C);

encoder Coder_left = vex::encoder(Brain.ThreeWirePort.G);
encoder Coder_right = vex::encoder(Brain.ThreeWirePort.E);