#include "vex.h"

using namespace vex;

const int UPDATETIME = 5;
const int MAXVOLTAGE = 12750;

brain Brain = brain();
controller Controller1 = controller(primary);

motor LF = motor(PORT10,ratio6_1,false);//端口未修改，正反转未修改
motor RF = motor(PORT10,ratio6_1,false);
motor LB = motor(PORT10,ratio6_1,false);
motor RB = motor(PORT10,ratio6_1,false);
motor LM = motor(PORT10,ratio6_1,false);
motor RM = motor(PORT10,ratio6_1,false);

inertial Inertial = inertial(PORT10);