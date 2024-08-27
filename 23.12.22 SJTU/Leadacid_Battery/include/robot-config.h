using namespace vex;

extern const int MAXVOLTAGE; 
extern const int UPDATETIME;

extern brain Brain;
extern controller Controller1;

extern motor LF;
extern motor LB;
extern motor RF;
extern motor RB;
extern motor LM;
extern motor RM;

extern motor Takein;

extern digital_out piston1;
extern digital_out piston2;
extern digital_out piston3;

extern inertial INERTIAL;

extern vision::signature Vision__S_GREEN;
extern vision::signature Vision__S_RED;
extern vision::signature Vision__S_BULE;

extern vision Vision;

void vexcodeInit(void);
