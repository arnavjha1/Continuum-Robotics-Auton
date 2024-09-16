#include "init.h"

using namespace vex;

#pragma region Devices

brain Brain;

// Robot configuration code.
motor leftMotorA = motor(PORT14, ratio6_1, true);
motor leftMotorB = motor(PORT19, ratio6_1, true);
motor leftMotorC = motor(PORT20, ratio6_1, true);
motor_group leftDriveSmart = motor_group(leftMotorA, leftMotorB, leftMotorC);
motor rightMotorA = motor(PORT15, ratio6_1, false);
motor rightMotorB = motor(PORT16, ratio6_1, false);
motor rightMotorC = motor(PORT16, ratio6_1, false);
motor_group rightDriveSmart = motor_group(rightMotorA, rightMotorB, rightMotorC);
drivetrain Drivetrain = drivetrain(leftDriveSmart, rightDriveSmart, 299.24, 295, 40, mm, 0.6666666666666666);

motor Intake = motor(PORT6, ratio18_1, false);

digital_out MogoPneu = digital_out(Brain.ThreeWirePort.B);
digital_out IntakePneu = digital_out(Brain.ThreeWirePort.A);

inertial InertialSensor = inertial(PORT13);

controller Controller1 = controller(primary);

#pragma endregion Devices

#pragma region initFunctions

// generating and setting random seed
void initializeRandomSeed(){
    int systemTime = Brain.Timer.systemHighResolution();
    double batteryCurrent = Brain.Battery.current();
    double batteryVoltage = Brain.Battery.voltage(voltageUnits::mV);

    // Combine these values into a single integer
    int seed = int(batteryVoltage + batteryCurrent * 100) + systemTime;

    // Set the seed
    srand(seed);
}

//Initializing random seed.
void vexcodeInit() {
    initializeRandomSeed(); 
}

#pragma endregion initFunctions