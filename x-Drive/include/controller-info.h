#ifndef CONTROLLER_INFO_H_
#define CONTROLLER_INFO_H_

#include "vex.h"
using namespace vex;

template<typename T>
void print_info(T info,int row,int col);//显示信息

void clear_info();//清屏
void clear_info(int row);//清行

int get_battery();//获取电池电量
int get_time();//获取时间

void print_time_battery();//显示电量和时间
void boot_animation();//开机动画
void boot_check(competition* cpt);//开机自检
void selection();

#endif