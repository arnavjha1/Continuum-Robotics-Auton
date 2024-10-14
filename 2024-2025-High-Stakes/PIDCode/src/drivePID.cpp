#include <main.h>
#include <init.h>
#include <drivePID.h>

using namespace vex;

#pragma region GlobalVars

float wheelDiameter = 3.25;
float pi = 3.14159;
float circ = wheelDiameter*pi;
float gearRatio = 1.33; // Driven/Driving (48/36)

float distToDrive = 0.0;

bool driveCrookedEnabled = false;

#pragma endregion GlobalVars

#pragma region DrivePID

int driveCrooked() {
    float finalL = distToDrive/circ*gearRatio*360;
    float finalR = distToDrive/circ*gearRatio*360;

    float kp = 0.05;
    float kd = 0.1;

    float prevL = 20.0;
    float prevR = 20.0;
    float currentL = 0.0;
    float currentR = 0.0;

    float lastErrorL;
    float lastErrorR;
    float proportionL;
    float proportionR;
    float derivativeL;
    float derivativeR;

    leftDriveSmart.setPosition(0, degrees);
    rightDriveSmart.setPosition(0, degrees);

    leftDriveSmart.setVelocity(100, percent);
    rightDriveSmart.setVelocity(100, percent);

    Drivetrain.drive(forward);

    while (driveCrookedEnabled) {
        float errorL = finalL-(leftMotorA.position(degrees)+leftMotorB.position(degrees)+leftMotorC.position(degrees))/3.0;
        float errorR = finalR-(rightMotorA.position(degrees)+rightMotorB.position(degrees)+rightMotorC.position(degrees))/3.0;
        float leftDist = errorL/360*gearRatio*circ;
        float rightDist = errorR/360*gearRatio*circ;
            
        if (fabs(leftDist) < 0.5 && fabs(rightDist) < 0.5) {
            Controller1.Screen.print(InertialSensor.heading());
            driveCrookedEnabled = false;
            break;
        }
            
        proportionL = errorL*kp;
        proportionR = errorR*kp;
        derivativeL = (errorL-lastErrorL)*kd;
        derivativeR = (errorR-lastErrorR)*kd;

        currentL = proportionL+derivativeL;
        currentR = proportionR+derivativeR;
        if (currentL < prevL-10) {
            currentL = prevL-10;
        }
        if (currentR < prevR-10) {
            currentR = prevR-10;
        }

        lastErrorL = errorL;
        lastErrorR = errorR;
        prevL = currentL;
        prevR = currentR;

        leftDriveSmart.setVelocity(currentL, percent);
        rightDriveSmart.setVelocity(currentR, percent);

        wait(5, msec);
    }
    Drivetrain.stop();

    return 1;
}

void drivePID(float dist) {
    float originalDir = InertialSensor.heading(degrees);

    float kp = 0.0;
    float kd = 0.0;

    float finalAmount;

    float lastError;
    float proportion;
    float derivative;

    distToDrive = dist;

    
    vex::task driveTask(driveCrooked);
    driveCrookedEnabled = true;

    wait(0.1, sec);

    while (driveCrookedEnabled) {
        float error = originalDir-InertialSensor.heading(degrees);

        proportion = error*kp;
        derivative = (error-lastError)*kd;

        lastError = error;

        finalAmount = proportion+derivative;

        leftDriveSmart.setVelocity(leftDriveSmart.velocity(percent)+finalAmount, percent);
        rightDriveSmart.setVelocity(rightDriveSmart.velocity(percent)-finalAmount, percent);

        wait(20, msec);
    }
    
    driveCrookedEnabled = false;
    driveTask.stop();
    
}

#pragma endregion DrivePID