#include "control-lib.h"

Chassis::Chassis(float _yaw , float _R){
    yaw = _yaw ;
    center_vel_y = 0 , center_vel_x = 0 ;
    world_vel_y = 0 , world_vel_x = 0 ;
    angular_vel = 0 ;
    sin_yaw = 0.0 , cos_yaw = 0.0 ;
    for(int i = 0 ; i < 4 ; i++){
        vel_list[i] = 0 ;
    }
    R = _R ;
}

void Chassis::set_vel_list(float * vel){
    for(int i = 0 ; i < 4 ; i++){
        vel_list[i] = vel[i];
    }
}

void Chassis::set_brake_type(vex::brakeType type_a){
    lf.setBrake(type_a);
    rf.setBrake(type_a);
    lb.setBrake(type_a);
    rb.setBrake(type_a);
}

void Chassis::chassis_movement(){
    rf.spin(fwd , (vel_list[0] / 100) * MAXVOLTAGE , vex::voltageUnits::mV);
    lf.spin(fwd , (vel_list[1] / 100) * MAXVOLTAGE , vex::voltageUnits::mV);
    lb.spin(fwd , (vel_list[2] / 100) * MAXVOLTAGE , vex::voltageUnits::mV);
    rb.spin(fwd , (vel_list[3] / 100) * MAXVOLTAGE , vex::voltageUnits::mV);
}

void OPChassis::get_controller(float Y_dead_zone , float X_dead_zone , float angluar_dead_zone){
    world_vel_x = (Controller1.Axis4.position() < X_dead_zone ? 0 : Controller1.Axis4.position())/1.1;
    world_vel_y = (Controller1.Axis3.position() < Y_dead_zone ? 0 : Controller1.Axis3.position())/1.1;
    angular_vel = (Controller1.Axis1.position() < angluar_dead_zone ? 0 : Controller1.Axis1.position());
}

void OPChassis::op_chassis_movement_by_man(){//Man! What can I say? Mamba out!
    yaw = 180 - Inertial.heading();
    sin_yaw = Sin(yaw);
    cos_yaw = Cos(yaw);
    vel_list[0] = ((-cos_yaw - sin_yaw) * world_vel_x + (-sin_yaw + cos_yaw) * world_vel_y + R * angular_vel) / sqrt(2);
    vel_list[1] = ((-cos_yaw + sin_yaw) * world_vel_x + (-sin_yaw - cos_yaw) * world_vel_y + R * angular_vel) / sqrt(2);
    vel_list[2] = ((cos_yaw + sin_yaw) * world_vel_x + (sin_yaw - cos_yaw) * world_vel_y + R * angular_vel) / sqrt(2);
    vel_list[3] = ((cos_yaw - sin_yaw) * world_vel_x + (sin_yaw + cos_yaw) * world_vel_y + R * angular_vel) / sqrt(2);

    chassis_movement();
}

void OPChassis::op_chassis_movement_by_car(){
    vel_list[0] = world_vel_x - world_vel_y - angular_vel;
    vel_list[1] = world_vel_x + world_vel_y + angular_vel;
    vel_list[2] = world_vel_x - world_vel_y + angular_vel;
    vel_list[3] = world_vel_x + world_vel_y - angular_vel;

    chassis_movement();
}