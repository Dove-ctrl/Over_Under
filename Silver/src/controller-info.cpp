#include "controller-info.h"

int choose_prog = 0;
bool ready_for_cpt = false;

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
int prog(){return choose_prog;}

void initialize(){
    /* Navigation::getInstance();
    Navigation::getInstance()->set_coordinate(X0 , Y0); */
    AUTOchassis::getInstance();
    OPchassis::getInstance();
    Inertial.calibrate();
    /* Coder_left.resetRotation();
    Coder_right.resetRotation(); */
    LB.resetPosition();
    RB.resetPosition();
}

void self_check(competition* cpt){
    //自检准备
    clear_info();
    print_info("请断开场控" , 1 , 8);
    print_info("并架起机器" , 2 , 8);
    print_info("按A以继续" , 3 , 8);
    waitUntil(!(cpt->isCompetitionSwitch()||cpt->isFieldControl()));
    while(true){
        if(Controller1.ButtonA.pressing()){waitUntil(!Controller1.ButtonA.pressing());break;}
        wait(UPDATETIME*2,msec);
    }

    //开始自检
    clear_info();
    int error_num=0;
    if(Inertial.installed()){print_info("陀螺仪正常",1,2);print_info("v ",3,1);}
    else{print_info("陀螺仪未连接",1,2);print_info("x ",3,1);error_num++;}
    wait(1000,msec);
    if(Brain.Battery.capacity()>90){print_info("电量正常",2,2);print_info("v ",3,3);}
    else{print_info("电量低",2,2);print_info("x ",3,3);error_num++;}
    wait(1000,msec);
    clear_info(1);clear_info(2);

    print_info("底盘检查: ",1,2);
    int motor_check_list[8]; int Emotor_num=0; bool is_problem=false;
    motor_check_list[0]=LF.installed();
    motor_check_list[1]=LB.installed();
    motor_check_list[2]=RF.installed();
    motor_check_list[3]=RB.installed();
    motor_check_list[4]=LMF.installed();
    motor_check_list[5]=LMB.installed();
    motor_check_list[6]=RMF.installed();
    motor_check_list[7]=RMB.installed();
    print_info("底盘马达旋转中...",2,2);
    LF.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    LB.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    RF.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    RB.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    LMF.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    LMB.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    RMF.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    RMB.spinFor(fwd,1000,msec,50,velocityUnits::pct);wait(500,msec);
    wait(500,msec);
    for(int i=0;i<=7;i++){
        if(motor_check_list[i]==0){
            print_info(i,1,15+Emotor_num); Emotor_num+=2;
            is_problem=true;
        }
    }
    wait(1000,msec);
    if(!is_problem){print_info("底盘连接正常 ",1,2);print_info("v ",3,5);}
    else{print_info("x ",3,5);error_num++;}
    wait(2000,msec);
    if(error_num>0){
        clear_info(1);
        clear_info(2);
        for(int i=1;i<=10;i++){
            print_info("#发现问题#",2,7);
            wait(500,msec);
            clear_info(2);
            wait(500,msec);
        }
    }
    else{
        clear_info();
        print_info("#自检未发现问题#",2,3);
        for(int i=1;i<=2;i++){
            print_info("*** *** *** ***",1,4);
            print_info("*** *** *** ***",3,4);
            wait(500,msec);
            clear_info(1);clear_info(3);
            wait(500,msec);
        }
    }
    clear_info();
    print_info("#*#*#*#*#*#*#*#*" , 1 , 1);
    print_info(" 自检结束 请重启", 2 , 3);
    print_info("#*#*#*#*#*#*#*#*" , 3 , 1);
    while(true){wait(UPDATETIME,msec);}
}

void cpt_info(competition* cpt){
    //等待场控连接
    clear_info();
    print_info("#*#*#*#*#*#*#*#*" , 1 , 1);
    print_info("请接入场控" , 2 , 8);
    print_info("#*#*#*#*#*#*#*#*" , 3 , 1);
    wait(500,msec);
    waitUntil(cpt->isCompetitionSwitch()||cpt->isFieldControl());

    //启动赛局
    ready_for_cpt = true;
    clear_info();
    int start_col=1 , start_row=1;
    int k = 2;
    print_info("电池:",start_row,start_col);
    print_info("%% ||",start_row,start_col+10);
    print_info("时间:",start_row,start_col+15);
    Brain.Timer.clear();
    while(true){
        print_info(get_battery() , start_row , start_col+8);
        print_info(get_time() , start_row , start_col+23);
        if( LF.temperature(pct) >= 50 ||
            LB.temperature(pct) >= 50 ||
            RF.temperature(pct) >= 50 ||
            RB.temperature(pct) >= 50 ||
            LMF.temperature(pct) >= 50 ||
            LMB.temperature(pct) >= 50 ||
            RMF.temperature(pct) >= 50 ||
            RMB.temperature(pct) >= 50 
        ){print_info("电机温度过高" , 3 , 1);}
        wait(1000,msec);
        clear_info(2);
        if((k++)%2 == 0){print_info("2023-2024 over under" , 2 , 1);}
        else{print_info("world championship" , 2 , 3);}
    }     
}

void debug_info(competition* cpt){
    //启动赛局
    ready_for_cpt = true;
    clear_info();
    while(true){
        /* print_info(*(Navigation::getInstance()->get_coordinate()) , 1 ,1);
        print_info(*(Navigation::getInstance()->get_coordinate()+1) , 1 ,10); */
        /* print_info(Inertial.heading() , 2 , 1);
        if( LF.temperature(pct) >= 50 ||
            LB.temperature(pct) >= 50 ||
            RF.temperature(pct) >= 50 ||
            RB.temperature(pct) >= 50 ||
            LMF.temperature(pct) >= 50 ||
            LMB.temperature(pct) >= 50 ||
            RMF.temperature(pct) >= 50 ||
            RMB.temperature(pct) >= 50 
        ){print_info("电机温度过高" , 3 , 1);} */
        wait(100,msec);
    }
}

void info_main(void* p){
    competition* cpt = (competition*)p;

    //初始化阶段
    initialize();

    clear_info();
    print_info("#*#*#*#*#*#*#*#*" , 1 , 1);
    print_info("正在初始化机器人" , 2 , 4);
    for(int i = 1 ; i <= 18 ; i++){
        print_info("=" , 3 , i);
        wait(115,msec);
    }
    clear_info();
    print_info("#*#*#*#*#*#*#*#*" , 1 , 1);
    print_info("初始化完成" , 2 , 8);
    print_info("#*#*#*#*#*#*#*#*" , 3 , 1);
    //Controller1.rumble("-");
    wait(800,msec);

    //程序选择阶段
    choose_prog = 1;
    int exit = 0; int page = 1; int choose_exit = 0;
    if(cpt->isCompetitionSwitch()){//连上狗牌直接跳转调试
        exit = 1;choose_prog = 3;
    }else
    while(exit == 0){
        while(choose_exit == 0){
            if(page == 1){//第一页内容
                clear_info();
                print_info("* 联赛" , 1 , 1);
                print_info("* 技能赛" , 2 , 1);
                print_info("* 调试" , 3 , 1);
                while(page == 1){
                    print_info("<==" , choose_prog , 16);
                    if(Controller1.ButtonDown.pressing()){
                        waitUntil(!Controller1.ButtonDown.pressing());
                        print_info("       " , choose_prog , 16);
                        if(choose_prog == 3){choose_prog=1,page=2;}
                        else{choose_prog++;}
                    }
                    else if(Controller1.ButtonUp.pressing()){
                        waitUntil(!Controller1.ButtonUp.pressing());
                        print_info("       " , choose_prog , 14);
                        (choose_prog == 1 ? choose_prog=1 : choose_prog--);
                    }
                    else if(Controller1.ButtonA.pressing()){
                        waitUntil(!Controller1.ButtonA.pressing());
                        choose_exit = 1;
                        break;
                    }
                    wait(UPDATETIME,msec);
                }
            }else if(page == 2){//第二页内容
                clear_info();
                print_info("* 自检" , 1 , 1);
                while(page == 2){
                    print_info("<==" , choose_prog , 16);
                    if(Controller1.ButtonDown.pressing()){
                        waitUntil(!Controller1.ButtonDown.pressing());
                        print_info("       " , choose_prog , 16);
                        (choose_prog == 3 ? choose_prog=3 : choose_prog--);
                    }
                    else if(Controller1.ButtonUp.pressing()){
                        waitUntil(!Controller1.ButtonUp.pressing());
                        print_info("       " , choose_prog , 14);
                        if(choose_prog == 1){choose_prog=3,page=1;}
                        else{choose_prog--;}
                    }
                    else if(Controller1.ButtonA.pressing()){
                        waitUntil(!Controller1.ButtonA.pressing());
                        choose_exit = 1;
                        break;
                    }
                    wait(UPDATETIME,msec);
                }
            }
            wait(UPDATETIME,msec);
        }

        //确认阶段
        clear_info();
        choose_exit = 0;
        print_info("按A确认       按B退出" , 3 , 1);
        print_info("确认进入" , 1 , 9);
        if(choose_prog == 1 && page == 1){print_info("\" 联赛 \" ?" , 2 , 7);}
        else if(choose_prog == 2 && page == 1){print_info("\" 技能赛 \" ?" , 2 , 7);}
        else if(choose_prog == 3 && page == 1){print_info("\" 调试 \" ?" , 2 , 7);}
        else if(choose_prog == 1 && page == 2){print_info("\" 自检 \" ?" , 2 , 7);choose_prog = 4;}
        while(true){
            if(Controller1.ButtonB.pressing()){
                waitUntil(!Controller1.ButtonB.pressing());
                exit = 0;choose_prog = 1;
                break;
            }
            else if(Controller1.ButtonA.pressing()){
                waitUntil(!Controller1.ButtonA.pressing());
                exit = 1;
                break;
            }
            wait(UPDATETIME,msec);
        }
        wait(UPDATETIME,msec);
    }

    if(choose_prog == 1 || choose_prog == 2){//赛局信息显示
        cpt_info(cpt);
    }else if(choose_prog == 4){//自检信息显示
        ready_for_cpt = true;
    }else if(choose_prog == 3){//调试信息显示
        debug_info(cpt);
    }            
}