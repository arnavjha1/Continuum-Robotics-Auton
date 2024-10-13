#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftFront = motor(PORT14, ratio6_1, true);
motor LeftBack = motor(PORT20, ratio6_1, true);
motor RightFront = motor(PORT15, ratio6_1, false);
motor RightBack = motor(PORT16, ratio6_1, false);
motor Left6th = motor(PORT19, ratio6_1, true);
motor Right6th = motor(PORT18, ratio6_1, false);
motor Arm = motor(PORT3, ratio18_1, false);
inertial Inertial13 = inertial(PORT13);
digital_out MogoPneu = digital_out(Brain.ThreeWirePort.B);
digital_out Claw = digital_out(Brain.ThreeWirePort.A);
digital_out Tipper = digital_out(Brain.ThreeWirePort.D);
motor Arm = motor(PORT9, ratio36_1, true);
motor Intake = motor(PORT6, ratio6_1, false);
limit LimitSwitchC = limit(Brain.ThreeWirePort.C);

void vexcodeInit( void ) {
  
}