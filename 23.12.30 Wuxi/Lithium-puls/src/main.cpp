#include "vex.h"
#include "opfunction.h"
#include "controllerinfo.h"
#include "autoroute.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  info_display("初始化 保持静止",1,1);
  Inertial.calibrate();
  waitUntil(!Inertial.isCalibrating());
  info_display("初始化成功!",1,1);
}

void autonomous(void) {
  info_display("正在为您自动下载原神",1,1);
  PlanA(&Competition);
  info_display("原神下载完成",1,1);
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
