#ifndef CHASSIS_H_
#define CHASSIS_H_

#include "PID.h"
#include "math-lib.h"
#include "control-lib.h"
using namespace vex;
using namespace std;

class Navigation{//机器人定位和导航
private:
    static Navigation* navigation;

    //定位系统
    float chassis_x;//位移矢量的大小
    float yaw;//偏航角
    float w;//机器位移角，位移矢量 与 机器x轴正方向 夹角
    float a;//世界位移角，位移矢量 与 世界x轴正方向 夹角
    float chassis_world_angle;//坐标相对角，机器坐标系 和 世界坐标系 夹角
    float chassis_L , chassis_R;//机器y轴方向位移 ， 机器x轴方向位移
    float world_Y , world_X;//世界y轴方向位移 ， 世界x轴方向位移
    float world_coordinate[2];// 机器在世界坐标系下的坐标(x,y)
    int sign_l , sign_r;//左右编码器值的符号

    //路径追踪系统
    

    Navigation();
public:
    static Navigation* getInstance(){
        if(navigation == NULL){ navigation = new Navigation(); }
        return navigation;
    }
    void set_coordinate(float x , float y);
    float* get_coordinate();
    void set_yaw(float input);

    void update_position(float kx);//定位
    float* pure_pursuit(float x , float y);//路径追踪
};

class OPchassis{//手动控制底盘
private:
    static OPchassis* opchassis;

    float liner_velocity , angular_velocity;
    float right_velocity , left_velocity;
    int left_deadzone , right_deadzone;

    OPchassis();
public:
    static OPchassis* getInstance(){
        if(opchassis == NULL){opchassis = new OPchassis(); }
        return opchassis;
    }
    int get_deadzone(turnType);
    void opchassis_movement(int left_adjust,int right_adjust);
    void get_controller(int liner_adjust,int angular_adjust);
    void set_deadzone(float ld,float rd);
    void opchassis_brake(brakeType);
    void set_direction();
    static void op_move(void* p);
    static void debug_op_move(void* p);
};

class AUTOchassis{//自动控制底盘
private:
    static AUTOchassis* autochassis;

    struct Yaw
    {
        float value;
        float operator+(const float& target_yaw) {
            if(target_yaw - this->value > 0){
                return target_yaw - this->value;
            }else{
                return 360 - this->value + target_yaw;
            }
        }
        float operator-(const float& target_yaw) {
            if(this->value - target_yaw > 0){
                return this->value - target_yaw;
            }else{
                return this->value + 360 - target_yaw;
            }
        }
    };
    
    float liner_velocity , angular_velocity;
    float left_velocity , right_velocity;
    float velocity;
    float position;
    Yaw current_yaw;
    float wheel_distance;

    PID liner_velocity_pid;
    PID liner_position_pid;
    PID angular_velocity_pid;
    PID angular_position_pid;
    timer T;

    AUTOchassis();

    float output_limit(float limit , float input);
    float get_velocity();
    float get_position();
    float get_yaw();
    void reset_postion();
    void reset_inertial();

    void forward(float vel , float d);
    void backward(float vel , float d);
    void turn_left_to(float vel , float angle);
    void turn_right_to(float vel , float angle);
    void left_curve(float vel , float angle , float ratio);
    void right_curve(float vel , float angle , float ratio);

    void route();
    void skill_route();
public:
    static AUTOchassis* getInstance(){
        if(autochassis == NULL){autochassis = new AUTOchassis(); }
        return autochassis;
    } 
    void autochassis_movement(int left_adjust , int right_adjust , bool reverse);
    void autochassis_movement();
    void autochassis_brake(brakeType a);
    //static void path_tracking(int loop_times);
    void run_auto_route(void* p);
    void run_skill_route(void* p);
    void debug_run_auto(void* p);
};

#endif