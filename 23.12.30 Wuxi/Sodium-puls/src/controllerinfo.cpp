#include "controllerinfo.h"
using namespace vex;

template<typename T>
void info_display(T info,int r,int c){
    info_clearline(r);
    Controller1.Screen.setCursor(r,c);
    Controller1.Screen.print(info);
}
template void info_display(int info,int r,int c);
template void info_display(double info,int r,int c);
template void info_display(const char *info,int r,int c);

void info_allclear(){
    Controller1.Screen.clearScreen();
}

void info_clearline(int a){
    Controller1.Screen.clearLine(a);
}

