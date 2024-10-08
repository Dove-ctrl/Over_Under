using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor LF;
extern motor LB1;
extern motor LB2;
extern motor RF;
extern motor RB1;
extern motor RB2;
extern motor mainTake;
extern motor Roller;
extern motor Fire;
extern motor A;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );