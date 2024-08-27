#ifndef CONTROL_LIB_H_
#define CONTROL_LIB_H_

#include "robot-config.h"

extern bool in ; extern bool out ;
extern bool lf ; extern bool rf ;
extern bool lb ; extern bool rb ;

void op_takein(void* p);
void auto_takein(void* p);

void op_piston(void* p);
void auto_piston(void* p);

void op_hang(void* p);

#endif