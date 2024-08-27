#ifndef CONTROLLER_INFO_H_
#define CONTROLLER_INFO_H_

#include "vex.h"

extern int choose_prog;
extern bool ready_for_cpt;

template<typename T>
void print_info(T info,int row,int col);//显示信息

void clear_info();//清屏
void clear_info(int row);//清行
int prog();
int get_battery();
int get_time();

void initialize();//初始化
void self_check(competition* cpt);//自检
void cpt_info(competition* cpt);//赛局信息显示
void debug_info(competition* cpt);//调试信息显示

void info_main(void* p);

#endif