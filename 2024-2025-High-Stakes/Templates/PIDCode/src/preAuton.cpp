#include <init.h>
#include <preAuton.h>

using namespace vex;

void preAuton() {
  leftMotorA.setVelocity(100, percent);
  leftMotorB.setVelocity(100, percent);
  leftMotorC.setVelocity(100, percent);
  rightMotorA.setVelocity(100, percent);
  rightMotorB.setVelocity(100, percent);
  rightMotorC.setVelocity(100, percent); 
  
  leftMotorA.setMaxTorque(100, percent);
  leftMotorB.setMaxTorque(100, percent);
  leftMotorC.setMaxTorque(100, percent);
  rightMotorA.setMaxTorque(100, percent);
  rightMotorB.setMaxTorque(100, percent);
  rightMotorC.setMaxTorque(100, percent); 

  leftMotorA.setStopping(brake);
  leftMotorB.setStopping(brake);
  leftMotorC.setStopping(brake);
  rightMotorA.setStopping(brake);
  rightMotorB.setStopping(brake);
  rightMotorC.setStopping(brake);

  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(100, percent); 

  InertialSensor.calibrate();
  InertialSensor.setHeading(0, degrees);
  InertialSensor.setRotation(0, degrees);
  
  Controller1.Screen.print("Calibrated");
}
