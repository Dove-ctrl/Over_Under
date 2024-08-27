#include "vision.h"
using namespace vex;

object get_triball(signature sig){
    Vision.takeSnapshot(sig);
    return Vision.largestObject;
}

object get_goal(signature sig){
    Vision.setSignature(sig);
    return Vision.largestObject;
}