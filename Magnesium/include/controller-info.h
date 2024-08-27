#ifndef CONTROLLER_INFO_H_
#define CONTROLLER_INFO_H_

#include "vex.h"
using namespace vex;

template<typename T>
void print_info(T info,int row,int col);

/*template void print_info(int info,int l,int r);
template void print_info(double info,int l,int r);
template void print_info(const char* info,int l,int r);*/ //实例化未定义？

void clear_info();
void clear_info(int row);

double get_battery();
int get_time();

#endif