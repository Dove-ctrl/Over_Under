#include "vex.h"
#include "opfunction.h"
#include "controller-info.h"

using namespace vex;

competition Competition;
competition* cpt = &Competition;

void pre_auton(void) {
  
}

void autonomous(void) {
  
}

void usercontrol(void) {
  thread chassis(op_move,cpt);
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}