#include "opfunction.h"
using namespace vex;

void op_move(void* p){
    competition* _p= (competition*)p;
    OPchassis op_chassis = OPchassis();
    op_chassis.set_deadzone(5,5);
    while(_p->isDriverControl()){
        if(Controller1.Axis3.position()<=op_chassis.left_deadzone &&
        Controller1.Axis1.position()<=op_chassis.right_deadzone){
            op_chassis.opchassis_brake(brake);
        }
        op_chassis.get_controller();
        op_chassis.opchassis_movement();
        this_thread::sleep_for(UPDATETIME);
    }
}