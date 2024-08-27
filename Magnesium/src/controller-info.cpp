#include "controller-info.h"

template<typename T>
void print_info(T info,int row,int col){
    Controller1.Screen.clearLine(row);
    Controller1.Screen.setCursor(row,col);
    Controller1.Screen.print(info);
}

void clear_info(){
    Controller1.Screen.clearScreen();
}
void clear_info(int row){
    Controller1.Screen.clearLine(row);
}

double get_battery(){
    return Brain.Battery.current();
}

int get_time(){
    return Brain.Timer.time(sec);
}