#include "autoroute.h"

void PlanA(competition* arg){
    AUTOchassis base;

    Inertial.setHeading(180,deg);
    Spread.setVelocity(90,pct);

    base.forward(40,1.6);
    wait(2000,msec);
    Spread.spinFor(fwd,380,msec);
    base.turn_right(45);
    base.forward(0,0.2);
    Spread.spinFor(reverse,380,msec);
    Spread.spinFor(fwd,380,msec);
    wait(300,msec);
    base.turn_right(90);
    base.forward(10,0.2);
    Spread.spinFor(reverse,380,msec);
    Spread.spinFor(fwd,380,msec);
    base.forward(5,0.2);
    base.turn_right(120);
    Spread.spinFor(reverse,380,msec);
    Spread.spinFor(fwd,380,msec);

    base.turn_right(90);
    Spread.spinFor(reverse,380,msec);
    base.backward(20,1);
    base.forward(5,0.15);
    base.turn_left(1);
    base.backward(3,2.2);
    base.forward(5,0.9);
    base.turn_right(45);
    base.backward(20,0.9);


    
    Spread.spinFor(fwd,380,msec);
    repeat(10){
        Arm.spinFor(fwd,600,msec);
        wait(300,msec);
        Arm.spinFor(reverse,600,msec);
    }
    wait(600,msec);

    base.turn_right(110);
    base.forward(40,0.6);
    base.backward(20,0.3);
    Spread.spinFor(reverse,380,msec);
    Arm.spinFor(fwd,700,msec);
    base.forward(40,3.3);
    Arm.spinFor(reverse,700,msec);

    base.turn_left(60);
    base.forward(40,1.5);

}