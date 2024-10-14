#include "vexcommon.h"

using namespace vex;

#pragma region variables

extern brain Brain;

// Robot configuration code.
extern motor leftMotorA;
extern motor leftMotorB;
extern motor leftMotorC;
extern motor_group leftDriveSmart;
extern motor rightMotorA;
extern motor rightMotorB;
extern motor rightMotorC;
extern motor_group rightDriveSmart;
extern drivetrain Drivetrain;

extern motor Intake;

extern digital_out MogoPneu;
extern digital_out IntakePneu;
extern digital_out HookPneu;

extern inertial InertialSensor;

extern controller Controller1;

#pragma endregion variables

#pragma region functions

void initializeRandomSeed();

void vexcodeInit();

#pragma endregion functions