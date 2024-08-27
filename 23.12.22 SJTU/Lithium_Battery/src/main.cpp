#include "vex.h"
#include "chassis.h"
#include "opfunction.h"
#include "controllerinfo.h"
#include "autoroute.h"

#define COMPILER 1
// 1 for user control, 0 for debug

using namespace vex;
competition Competition;

void pre_auton(void) {
  info_display("初始化 保持静止",1,1);
  INERTIAL.calibrate();
  waitUntil(!INERTIAL.isCalibrating());
  clearline(1);
  info_display("初始化成功!",1,1);
}

void autonomous(void) {
  clearline(1);
  info_display("自动程序已启动",1,1);
  PlanA(&Competition);
  clearline(1);
  info_display("自动程序结束",1,1);
}

void usercontrol(void) {
  #if COMPILER == 1 // user control
  clearline(1);
  info_display("手动程序已启动",1,1);
  thread _base(op_movement);
  thread _arm(arm_control);
  thread _takein(takein_control);
  thread _shoot(shoot_control);
  thread _piston(piston_control);

  #elif COMPILER == 0 // debug

  #endif
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}