#include <init.h>
#include <subsystems.h>
#include <userControl.h>

using namespace vex;

void arcade() {
  double driveSpeed = 0.4;
  while (1) {
    int pos = Controller1.Axis1.position()+2;
    leftDriveSmart.setVelocity(driveSpeed*(Controller1.Axis3.position()+pos), percent);
    rightDriveSmart.setVelocity(driveSpeed*(Controller1.Axis3.position()-pos), percent);
    leftDriveSmart.spin(forward);
    rightDriveSmart.spin(forward);

    wait(5, msec);
  }
}

void tank() {
    double driveSpeed = 1.0;
    while (1) {
      leftDriveSmart.setVelocity(driveSpeed*Controller1.Axis3.position(), percent);
      rightDriveSmart.setVelocity(driveSpeed*Controller1.Axis2.position(), percent);
      leftDriveSmart.spin(forward);
      rightDriveSmart.spin(forward);

      wait(5, msec);
    }
}

void userControl() { 
  // Intake motor: Port 6
  // Left 1: 14 
  // Left 2: 19 
  // Left 3: 20 
  // Right 1: 15
  // Right 2: 16
  // Right 3: 18
  Controller1.ButtonL1.pressed(spinIntakeForward);
  Controller1.ButtonL1.released(stopIntake);

  Controller1.ButtonL2.pressed(spinIntakeReverse);
  Controller1.ButtonL2.released(stopIntake); 

  Controller1.ButtonR1.pressed(triggerMogoMech);
  
  Controller1.ButtonUp.pressed(triggerIntakePneu);
  
  Controller1.ButtonR2.pressed(triggerHookPneu);
  
  // place driver control in this while loop
  tank();
}