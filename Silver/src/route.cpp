#include "chassis.h"

void AUTOchassis::route(){
    in = true;
    forward(100,1.1);
    turn_right_to(70,45);
    forward(50,0.3);
    backward(50,0.3);
    in = false;
}

void AUTOchassis::skill_route(){
    
}