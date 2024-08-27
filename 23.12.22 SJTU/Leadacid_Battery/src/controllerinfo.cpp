#include "controllerinfo.h"
using namespace vex;

template<typename T>
void info_display(T info,int r,int c){
    Controller1.Screen.clearLine(r);
    Controller1.Screen.setCursor(r,c);
    Controller1.Screen.print(info);
}
template void info_display(int info,int r,int c);
template void info_display(double info,int r,int c);
template void info_display(const char *info,int r,int c);

void allclear(){
    Controller1.Screen.clearScreen();
}

void clearline(int a){
    Controller1.Screen.clearLine(a);
}

