#include <init.h>
#include <preAuton.h>

using namespace vex;

void preAuton() {
  Drivetrain.setDriveVelocity(100, percent);
  Drivetrain.setTurnVelocity(100, percent);
  
  leftDriveSmart.setMaxTorque(100, percent);
  rightDriveSmart.setMaxTorque(100, percent);

  Drivetrain.setStopping(coast);

  leftDriveSmart.setPosition(0, degrees);
  rightDriveSmart.setPosition(0, degrees);

  Intake.setStopping(coast);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(100, percent); 

  InertialSensor.calibrate();
  InertialSensor.setHeading(0, degrees);
  InertialSensor.setRotation(0, degrees);
  
  Controller1.Screen.print("Calibrated");
}
