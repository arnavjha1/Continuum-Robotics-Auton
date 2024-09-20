#include <init.h>
#include <drivePID.h>

using namespace vex;

#pragma region GlobalVars

float wheelDiameter = 3.25;
float pi = 3.14159;
float circ = wheelDiameter*pi;
float gearRatio = 1.33; // Driven/Driving (48/36)

#pragma endregion GlobalVars

#pragma region DrivePID

void drivePID(float dist) {
    float finalL = dist/circ*gearRatio*360;
    float finalR = dist/circ*gearRatio*360;

    float kp = 0.4;
    float kd = 0.2;

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

    Drivetrain.drive(forward);

    while (true) {
        float errorL = finalL-(leftMotorA.position(degrees)+leftMotorB.position(degrees)+leftMotorC.position(degrees))/3.0;
        float errorR = finalR-(rightMotorA.position(degrees)+rightMotorB.position(degrees)+rightMotorC.position(degrees))/3.0;
        float leftDist = errorL/360*gearRatio*circ;
        float rightDist = errorR/360*gearRatio*circ;
        
        if (fabs(errorR/360*gearRatio*circ) < 0.5 && fabs(errorR/360*gearRatio*circ) < 0.5) {
            Controller1.Screen.print((leftDist+rightDist)/2.0);
            break;
        }
        
        proportionL = errorL*kp;
        proportionR = errorR*kp;
        derivativeL = (errorL-lastErrorL)*kd;
        derivativeR = (errorR-lastErrorR)*kd;

        lastErrorL = errorL;
        lastErrorR = errorR;

        currentL = proportionL+derivativeL;
        currentR = proportionR+derivativeR;

        leftDriveSmart.setVelocity(currentL, percent);
        rightDriveSmart.setVelocity(currentR, percent);

        wait(5, msec);
    }

    Drivetrain.stop();
}

#pragma endregion DrivePID