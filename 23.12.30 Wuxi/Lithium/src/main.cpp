#include "vex.h"
#include "opfunction.h"
#include "controllerinfo.h"
#include "autoroute.h"

using namespace vex;

competition Competition;

#define OPMODE 1 //1 = user control, 2 = debug
#define AUTOMODE 2 //1 = auto control, 2 = debug

void pre_auton(void) {
  info_display("校准中,不要移动",1,1);
  Inertial.calibrate();
  waitUntil(!Inertial.isCalibrating());
  info_display("校准成功!原神,启动!",1,1);
}

void autonomous(void) {
  #if AUTOMODE==1
  info_display("自动程序已启动",1,1);
  PlanA(&Competition);
  info_display("自动程序结束",1,1);

  #elif AUTOMODE==2
  info_display("调试程序已启动",1,1);
  debug(&Competition);
  info_display("调试程序结束",1,1);

  #endif
}

void usercontrol(void) {
  info_display("正在执行手动程序",1,1);
  thread opbase(op_movement,&Competition);
  thread oparm(op_arm,&Competition);
  thread optake(op_Spread,&Competition);
  thread oppision(op_Sidehang,&Competition);
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  pre_auton();
  while (true) {
    wait(100, msec);
  }
}