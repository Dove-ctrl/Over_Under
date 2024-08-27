#include "vex.h"
#include "controller-info.h"
#include "control-lib.h"

using namespace vex;

competition Competition = competition();
/* Navigation* Navigation::navigation = NULL; */
OPchassis* OPchassis::opchassis = NULL;
AUTOchassis* AUTOchassis::autochassis = NULL;

void autonomous(void) {
  waitUntil(ready_for_cpt);
  if(prog() == 1){//联赛

    AUTOchassis::getInstance()->run_auto_route(&Competition);

  }else if(prog() == 2){//技能赛

    AUTOchassis::getInstance()->run_skill_route(&Competition);

  }else if(prog() == 3){//调试

    AUTOchassis::getInstance()->debug_run_auto(&Competition);

  }
}

void usercontrol(void) {
  waitUntil(ready_for_cpt);
  if(prog() == 1 || prog() == 2){//联赛，技能赛

    thread(OPchassis::op_move,&Competition);
    thread(op_takein,&Competition);
    thread(op_piston,&Competition);
    thread(op_hang,&Competition);

  }else if(prog() == 3){//调试

    thread(OPchassis::debug_op_move,&Competition);
    thread(op_takein,&Competition);
    thread(op_piston,&Competition);
    thread(op_hang,&Competition);

  }else if(prog() == 4){//自检
    self_check(&Competition);
  }
}

void pre_auton(void) {
  thread(info_main,&Competition);
}

int main() {
  pre_auton();
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);
  while (true) {
    wait(100, msec);
  }
}