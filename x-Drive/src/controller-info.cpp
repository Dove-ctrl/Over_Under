#include "controller-info.h"

template<typename T>
void print_info(T info,int row,int col){
    Controller1.Screen.setCursor(row,col);
    Controller1.Screen.print(info);
}

template void print_info(int info,int row,int col);
template void print_info(double info,int row,int col);
template void print_info(char* info,int row,int col);
template void print_info(const char* info,int row,int col);

void clear_info(){Controller1.Screen.clearScreen();}
void clear_info(int row){Controller1.Screen.clearLine(row);}
int get_battery(){return Brain.Battery.capacity();}
int get_time(){return Brain.Timer.time(sec);}

void print_time_battery(){
    int start_col=1 , start_row=1;
    print_info("电池:",start_row,start_col);
    print_info("%% ||",start_row,start_col+10);
    print_info("时间:",start_row,start_col+15);
    print_info("==== USST VEX ====",2,1);
    Brain.Timer.clear();
    while(true){
        print_info(get_battery(),start_row,start_col+8);
        print_info(get_time(),start_row,start_col+23);
        this_thread::sleep_for(1000);
    }                                                                                                                           
}

void boot_animation(){
    clear_info();
    const char* str1[17]={"P","r","o","g","r","a","m","e","d"," ","b","y"," ","D","o","v","e"};
    const char* str2[17]={" "," ","W","o","r","k"," ","w","i","t","h"," ","j","i","n"," "," "};
    const char* str3[17]={"S","u","p","p","o","r","t","e","d"," ","b","y"," ","U","S","S","T"};
    for(int i=0;i<17;i++){
        print_info(str1[i],1,2+i);
        print_info(str2[i],2,4+i);
        print_info(str3[i],3,2+i);
        wait(10,msec);
    }
    wait(1000,msec);
    for(int i=1;i<=22;i++){
        print_info(" |||||||",1,i);
        print_info(" |||||||",2,i);
        print_info(" |||||||",3,i);
    }
    clear_info();
}

void boot_check(competition* cpt){
    /*print_info("#准备进行赛前自检#",2,2);
    for(int i=1;i<=4;i++){
        print_info("*** *** *** ***",1,4);
        print_info("*** *** *** ***",3,4);
        wait(500,msec);
        clear_info(1);clear_info(3);
        wait(500,msec);
    }
    int error_num=0;
    clear_info();

    if(cpt->isFieldControl()||cpt->isCompetitionSwitch()){print_info("场控已连接",1,2);print_info("v ",3,1);}
    else{print_info("场控未连接",1,2);print_info("x ",3,1);error_num++;}
    wait(1000,msec);
    if(Inertial.installed()){print_info("陀螺仪已连接",2,2);print_info("v ",3,3);}
    else{print_info("陀螺仪未连接",2,2);print_info("x ",3,3);error_num++;}
    wait(1000,msec);
    clear_info(1);clear_info(2);

    if(Brain.Battery.capacity()>70){print_info("电量正常",1,2);print_info("v ",3,5);}
    else{print_info("电量低",1,2);print_info("x ",3,5);error_num++;}
    wait(1000,msec);
    if(Controller1.installed()){print_info("遥控器正常",2,2);print_info("v ",3,7);}
    else{print_info("遥控器异常",2,2);print_info("x ",3,7);error_num++;}
    wait(1000,msec);
    clear_info(1);clear_info(2);

    print_info("底盘检查: ",1,2);
    int motor_check_list[8]; int Emotor_num=0; bool is_problem=false;
    motor_check_list[0]=LF.installed();motor_check_list[1]=LMF.installed();
    motor_check_list[2]=LMB.installed();motor_check_list[3]=LB.installed();
    motor_check_list[4]=RF.installed();motor_check_list[5]=RMF.installed();
    motor_check_list[6]=RMB.installed();motor_check_list[7]=RB.installed();
    for(int i=0;i<=5;i++){
        if(motor_check_list[i]==0){
            print_info(i,1,15+Emotor_num); Emotor_num+=2;
            is_problem=true;
        }
    }
    if(!is_problem){print_info("底盘正常 ",1,2);print_info("v ",3,9);}
    else{print_info("x ",3,9);error_num++;}
    if(error_num>0){
        for(int i=1;i<=15;i++){
            print_info("#发现问题#",2,7);
            wait(500,msec);
            clear_info(2);
            wait(500,msec);
        }
    }
    else{
        wait(1000,msec);
        clear_info();
        print_info("#自检未发现问题#",2,3);
        for(int i=1;i<=2;i++){
            print_info("*** *** *** ***",1,4);
            print_info("*** *** *** ***",3,4);
            wait(500,msec);
            clear_info(1);clear_info(3);
            wait(500,msec);
        }
    }*/
}