/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "basicfunction.h"
#include "autonomous.h"
#include <graphics.h>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  int v1,v3;
  int a;
  runauton();
  // User control code here, inside the loop
  /*while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.
    v1=Controller1.Axis1.position();
    v3=Controller1.Axis3.position();
    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //basicmove
    move((v3-v1),(v3+v1));

    //take
    take_roller(100);

    //shoot
    if(Controller1.ButtonA.pressing()){
      a=1;
    }else if(Controller1.ButtonL1.pressing()){
      a=0;
    }
    
    if(a==1){
      if(Controller1.ButtonA.pressing()){
        Fire.spin(fwd,100,pct);
      }else{
        Fire.stop(hold);
      }
    }else if(a==0){
      shoot(7,100);
    }
    
    if(Controller1.ButtonY.pressing()){
        Fire.spinFor(vex::directionType::fwd,4.5,vex::rotationUnits::rev,100,vex::velocityUnits::pct,false);
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }*/
}

//
// Main will set up the competition functions and callbacks.
//


int main()
{
    initgraph(640, 480);
    circle(200, 200, 200);

    getch();
    closegraph();

    return 0;
}

