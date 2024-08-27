#include "chassis.h"

Navigation::Navigation(){
    yaw = w = a = 0;
    chassis_L=chassis_R = 0;
    world_X=world_Y = 0;
    sign_l=0,sign_r=0;
    chassis_x = 0;
    /* chassis_world_angle = ANGLE; */
}

void Navigation::set_coordinate(float x , float y){
    world_coordinate[0] = x;
    world_coordinate[1] = y;
}

float* Navigation::get_coordinate(){
    static float coordinate[2];
    coordinate[0] = world_coordinate[0];
    coordinate[1] = world_coordinate[1];
    return coordinate;
}

void Navigation::set_yaw(float input){
    yaw = input;
}

/// @brief 更新坐标函数，对机器人在世界坐标系下，每个采样时间内的位移，进行积分，获取实时坐标
/// @param kx 坐标放缩倍率
void Navigation::update_position(float kx){
    chassis_L = -Coder_right.rotation(rotationUnits::rev);//记录机器坐标系下的位移
    chassis_R = Coder_left.rotation(rotationUnits::rev);
    sign_l = sign(chassis_L);//记录上述位移符号
    sign_r = sign(chassis_R);
    chassis_L = fabs(chassis_L);//符号和数值分离
    chassis_R = fabs(chassis_R);

    chassis_x = chassis_L * chassis_L + chassis_R * chassis_R;//计算位移矢量大小
    chassis_x = sqrt(chassis_x);

    if(sign_l == 0 && sign_r == 0){}//计算w
    else if(sign_l == 0 && sign_r != 0){w = (sign_r > 0 ? 0 : 180);}
    else if(sign_r == 0 && sign_l != 0){w = (sign_l > 0 ? 90 : 270);}
    else if(sign_l != 0 && sign_r != 0){
        if(sign_l > 0 && sign_r > 0){w = arctan(chassis_L / chassis_R);}
        else if(sign_l > 0 && sign_r < 0){w = 180 - arctan(chassis_L / chassis_R);}
        else if(sign_l < 0 && sign_r < 0){w = 180 + arctan(chassis_L / chassis_R);}
        else if(sign_l < 0 && sign_r > 0){w = 360 - arctan(chassis_L / chassis_R);}
    }

    //把 机器偏航角（机器相对于世界坐标系） 转化为 坐标系偏角（机器坐标系相对于世界坐标系）
    if(yaw <= chassis_world_angle && yaw > 0){yaw = chassis_world_angle - yaw;}
    else if(yaw <= 360 && yaw > 270 + chassis_world_angle){yaw = chassis_world_angle + 360 - yaw;}
    else if(yaw <= 270 + chassis_world_angle && yaw > chassis_world_angle){yaw = 90 + (360 - yaw) - (90 - chassis_world_angle);}

    a = w + yaw;//计算a

    world_X = kx * chassis_x * Cos(a);//计算世界坐标系下的位移
    world_Y = kx * chassis_x * Sin(a);//kx是坐标放缩倍率

    world_coordinate[0] = world_coordinate[0] + world_X;//更新坐标
    world_coordinate[1] = world_coordinate[1] + world_Y;

    Coder_left.resetRotation();//重置编码器
    Coder_right.resetRotation();
}

/// @brief 纯路径追踪函数，输入当前目标点坐标，根据当前位姿和目标点位姿，输出机器人的旋转半径和偏航角差值
/// @param x 目标点x坐标
/// @param y 目标点y坐标
/// @return 返回float数组，包含旋转半径和偏航角差值
float* Navigation::pure_pursuit(float x , float y){
    static float info_to_autochassis[2];

    return info_to_autochassis;
}