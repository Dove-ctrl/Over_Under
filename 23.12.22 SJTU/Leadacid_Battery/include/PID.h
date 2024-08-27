#ifndef PID_H_
#define PID_H_

#include "vex.h"

class PID{
    protected:
        float errorCurt,errorP,errorD,errorI;
        float P,I,D;
        bool firstTime;
        bool arrived;
        float kp,ki,kd; 
        float target,errorTol;
        float IMax,IMin;
        float output;
        timer T;
    public:
        PID();
        void resetfirstTime();
        void setCoefficient(float, float, float);
        void setTarget(float);
        void setIrange(float,float);
        void seterrorTol(float);
        virtual void update(float);
        bool targetArrived();
        float getoutput();
        void resetI();
        void resetoutput();
};

class PID_VariableI : public PID{
    private:
        float Phase,Smooth;
    public:
        void set_variable_param(float,float);
        float variable(float);
        void update(float);
};

#endif