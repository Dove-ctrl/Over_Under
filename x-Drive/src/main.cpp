#include "vex.h"
#include "control-lib.h"

using namespace vex;

competition Competition;

bool ready = false;

void pre_auton(void) {
  Inertial.calibrate();
  waitUntil(!Inertial.isCalibrating());
  Inertial.setHeading(0,deg);
  ready = true;
}

void autonomous(void) {

}

void usercontrol(void) {
  waitUntil(ready);

  
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
