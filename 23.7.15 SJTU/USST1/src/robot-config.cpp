#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor LF = motor(PORT18, ratio18_1, false);
motor LB1 = motor(PORT10, ratio18_1, false);
motor LB2 = motor(PORT9, ratio18_1, false);
motor RF = motor(PORT16, ratio18_1, true);
motor RB1 = motor(PORT5, ratio18_1, true);
motor RB2 = motor(PORT2, ratio18_1, true);
motor mainTake = motor(PORT20, ratio18_1, true);
motor Roller = motor(PORT19, ratio18_1, true);
motor Fire = motor(PORT1, ratio18_1, false);
motor A = motor(PORT6, ratio18_1 ,false);
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}