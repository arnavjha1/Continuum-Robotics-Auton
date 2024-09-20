#include <init.h>
#include <preAuton.h>

using namespace vex;

void preAuton() {
  leftDriveSmart.setVelocity(100, percent);
  rightDriveSmart.setVelocity(100, percent);
  
  leftDriveSmart.setMaxTorque(100, percent);
  rightDriveSmart.setMaxTorque(100, percent);

  leftDriveSmart.setStopping(brake);
  rightDriveSmart.setStopping(brake);

  leftDriveSmart.setPosition(0, degrees);
  rightDriveSmart.setPosition(0, degrees);

  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(100, percent); 

  InertialSensor.calibrate();
  InertialSensor.setHeading(0, degrees);
  InertialSensor.setRotation(0, degrees);
  
  Controller1.Screen.print("Calibrated");
}
