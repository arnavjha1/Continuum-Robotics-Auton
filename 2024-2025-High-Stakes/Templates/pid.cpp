
#pragma region VEXcode Generated Robot Configuration
// Make sure all required headers are included.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>


#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;


// START V5 MACROS
#define waitUntil(condition)                                                   \
  do {                                                                         \
    wait(5, msec);                                                             \
  } while (!(condition))

#define repeat(iterations)                                                     \
  for (int iterator = 0; iterator < iterations; iterator++)
// END V5 MACROS


// Robot configuration code.
motor Intake = motor(PORT11, ratio6_1, false);

digital_out FrontWingPneu = digital_out(Brain.ThreeWirePort.E);
digital_out BackWingPneu = digital_out(Brain.ThreeWirePort.D);
motor Catapult = motor(PORT9, ratio36_1, true);

motor leftMotorC = motor(PORT14, ratio6_1, true);

motor rightMotorC = motor(PORT18, ratio6_1, false);

motor leftMotorA = motor(PORT1, ratio6_1, true);
motor leftMotorB = motor(PORT12, ratio6_1, true);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT8, ratio6_1, false);
motor rightMotorB = motor(PORT20, ratio6_1, false);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial DrivetrainInertial = inertial(PORT13);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 0.6666666666666666);

controller Controller1 = controller(primary);
digital_out EndgamePneu = digital_out(Brain.ThreeWirePort.F);

void calibrateDrivetrain() {
  wait(200, msec);
  Brain.Screen.print("Calibrating");
  Brain.Screen.newLine();
  Brain.Screen.print("Inertial");
  DrivetrainInertial.calibrate();
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }

  // Clears the screen and returns the cursor to row 1, column 1.
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
}

// Helper to make playing sounds from the V5 in VEXcode easier and
// keeps the code cleaner by making it clear what is happening.
void playVexcodeSound(const char *soundName) {
  printf("VEXPlaySound:%s\n", soundName);
  wait(5, msec);
}



// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;
// define variables used for controlling motors based on controller inputs
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;

// define a task that will handle monitoring inputs from Controller1
int rc_auto_loop_function_Controller1() {
  // process the controller input every 20 milliseconds
  // update the motors based on the input values
  while(true) {
    if(RemoteControlCodeEnabled) {
      // stop the motors if the brain is calibrating
      if (DrivetrainInertial.isCalibrating()) {
        LeftDriveSmart.stop();
        RightDriveSmart.stop();
        while (DrivetrainInertial.isCalibrating()) {
          wait(25, msec);
        }
      }
      
      // calculate the drivetrain motor velocities from the controller joystick axies
      // left = Axis3
      // right = Axis2
      int drivetrainLeftSideSpeed = Controller1.Axis3.position();
      int drivetrainRightSideSpeed = Controller1.Axis2.position();
      
      // check if the value is inside of the deadband range
      if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
        // check if the left motor has already been stopped
        if (DrivetrainLNeedsToBeStopped_Controller1) {
          // stop the left drive motor
          LeftDriveSmart.stop();
          // tell the code that the left motor has been stopped
          DrivetrainLNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the left motor nexttime the input is in the deadband range
        DrivetrainLNeedsToBeStopped_Controller1 = true;
      }
      // check if the value is inside of the deadband range
      if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
        // check if the right motor has already been stopped
        if (DrivetrainRNeedsToBeStopped_Controller1) {
          // stop the right drive motor
          RightDriveSmart.stop();
          // tell the code that the right motor has been stopped
          DrivetrainRNeedsToBeStopped_Controller1 = false;
        }
      } else {
        // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
        DrivetrainRNeedsToBeStopped_Controller1 = true;
      }
      
      // only tell the left drive motor to spin if the values are not in the deadband range
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
        LeftDriveSmart.spin(forward);
      }
      // only tell the right drive motor to spin if the values are not in the deadband range
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
        RightDriveSmart.spin(forward);
      }
    }
    // wait before repeating the process
    wait(20, msec);
  }
  return 0;
}

task rc_auto_loop_task_Controller1(rc_auto_loop_function_Controller1);

#pragma endregion VEXcode Generated Robot Configuration

// ----------------------------------------------------------------------------
//                                                                            
//    Project: 1258V Alliance Routines                                            
//    Author: Anshul Raghav
//    Created: Nov 12 2023
//    Configuration:        
//                                                                            
// ----------------------------------------------------------------------------

// Include the V5 Library
#include "vex.h"

// Allows for easier use of the VEX Library
using namespace vex;
bool backWingPosition = false;
bool frontWingPosition = false;
float proportional, derivative, kd, integral, ki;
bool isShooting = false;

void shootCatapult() {
  Catapult.spin(forward);
}
void stopCatapult() {
  Catapult.stop();
}

void skillsCatapult() {
  if (!isShooting) {
    Catapult.spin(forward);
    isShooting = true;
  }
  else {
    Catapult.stop();
    isShooting = false;
  }
}

void spinIntakeForward() {
  Intake.spin(forward);
}
void spinIntakeReverse() {
  Intake.spin(reverse);
}
void stopIntake() {
  Intake.stop();
}

void toggleFrontWings() {
  if (frontWingPosition) {
    FrontWingPneu.set(false);
    frontWingPosition = false;
  }
  else {
    FrontWingPneu.set(true);
    frontWingPosition = true;
  }
}

void toggleBackWings() {
  if (backWingPosition) {
    BackWingPneu.set(false);
    backWingPosition = false;
  }
  else {
    BackWingPneu.set(true);
    backWingPosition = true;
  }
}

void toggleEndgame() {
  EndgamePneu.set(true);
}

// Begin project code

void printScreen(const char *message) {

  Brain.Screen.setFont(mono40);
  Brain.Screen.setPenColor(white);
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);
  Brain.Screen.print(message);
  Brain.Screen.newLine();
}

void stopDrivetrain(int numSeconds) {
  Brain.Timer.clear();
  waitUntil((Brain.Timer.time(seconds) > numSeconds));
  Drivetrain.stop();
}

void preAutonomous(void) {

  printScreen("Running Pre-Auton");  

  calibrateDrivetrain();

  Drivetrain.setHeading(0, degrees);
  Drivetrain.setRotation(0, degrees);
  Drivetrain.setStopping(coast);

  Catapult.setStopping(brake);
  Catapult.setMaxTorque(100, percent);
  Catapult.setVelocity(75, percent);

  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(85, percent);

  leftMotorA.setVelocity(100, percent);
  leftMotorB.setVelocity(100, percent);
  leftMotorC.setVelocity(66.67, percent);
  rightMotorA.setVelocity(100, percent);
  rightMotorB.setVelocity(100, percent);
  rightMotorC.setVelocity(66.67, percent);
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

  FrontWingPneu.set(false);
  BackWingPneu.set(false);
  EndgamePneu.set(false);

  printScreen("Pre-Auton Done");

  wait(1, seconds);
}


void PStraight(double dist, double velo) {
  Drivetrain.setDriveVelocity(velo, percent);
  Drivetrain.driveFor(forward, dist, inches, false);
  waitUntil((!Drivetrain.isMoving()));
}

void PStraightTime(double time, double velo) {
  Brain.Timer.clear();
  Drivetrain.drive(forward);
  Drivetrain.setDriveVelocity(velo, percent);
  waitUntil((Brain.Timer.time(seconds) > time));
  Drivetrain.stop();
}

int rightDist(int currentPos, int endPos) {
    int dist = endPos%360-currentPos%360;
    if (dist < 0) {
        dist += 360;
    }
    if (dist > 330) {
        return dist-360;
    }
    return dist;
}

int leftDist(int currentPos, int endPos) {
    int dist = currentPos%360-endPos%360;
    if (dist < 0) {
        dist += 360;
    }
    if (dist > 330) {
        return dist-360;
    }
    return dist;
}

void PRight(int desiredValue, double timeOut = 1.0) {
  Drivetrain.setTurnVelocity(100, percent);
  Drivetrain.setRotation(0, degrees);

  double kP = 0.2;
  double kD = 0.1;


  int error, previousError;
  int derivative;

  int currentHeading = (int)Drivetrain.heading()%360;

  Brain.Timer.clear();
  Drivetrain.turn(right);

  while ((abs(currentHeading-desiredValue) >= 1) && (Brain.Timer.time(seconds) < timeOut))  {
    error = rightDist(Drivetrain.heading(), desiredValue);
    derivative = error-previousError;
    previousError = error;

    double velocity = error*kP+derivative*kD;
    
    Drivetrain.setTurnVelocity(velocity, percent);

    currentHeading = (int)Drivetrain.heading()%360;

    wait(0.01, seconds);
  }

  Drivetrain.stop();
}

void PLeft(int desiredValue, double timeOut = 1.0) {
  Drivetrain.setTurnVelocity(100, percent);
  Drivetrain.setRotation(0, degrees);

  double kP = 0.2;
  double kD = 0.1;

  int error, previousError;
  int derivative;

  int currentHeading = (int)Drivetrain.heading()%360;

  Brain.Timer.clear();

  Drivetrain.turn(left);

  while (abs(desiredValue-currentHeading) > 1 && (Brain.Timer.time(seconds) < timeOut)) {
    error = leftDist(Drivetrain.heading(), desiredValue);
    derivative = error-previousError;
    previousError = error;

    double velocity = error*kP+derivative*kD;
    
    Drivetrain.setTurnVelocity(velocity, percent);

    currentHeading = (int)Drivetrain.heading()%360;
  }
  Brain.Screen.print(360-Drivetrain.heading());
  Drivetrain.stop();
}

void frontAuton(void) {
  printScreen("Running Auton");  

  Drivetrain.setHeading(0, degrees);
  Drivetrain.setRotation(0, degrees);

  Catapult.setStopping(brake);  
  Catapult.setMaxTorque(100, percent);
  Catapult.setVelocity(75, percent);
  
  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(85, percent);

  //WingPneu.set(false);
  //IntakePneu.set(false);
  PStraight(10, 100);
  //WingPneu.set(true);
  PStraight(-8, 100);
  //WingPneu.set(false);
  //IntakePneu.set(true);
  PLeft(75);
  PStraight(54, 100);
  /*
  //PTurn(45);
  Brain.Timer.clear();
  Drivetrain.turnFor(right, 30, degrees, false);
  waitUntil((Brain.Timer.time(seconds) > 1.5) || !Drivetrain.isMoving());
  Drivetrain.stop();
  IntakePneu.set(false);
  Intake.spin(reverse);
  PStraightTime(1, 100);
  //wait(0.2, seconds);
  //PStraight(-8, 100);
  //PStraight(8, 100);
  PStraight(-5, 100);
  PTurn(45);
  PStraightTime(2, -100);
  //PTurn(-135);
  Brain.Timer.clear();
  Drivetrain.turnFor(right, 90, degrees, false);
  waitUntil((Brain.Timer.time(seconds) > 1.5) || !Drivetrain.isMoving());
  Drivetrain.stop();
  PStraight(26, 100);
  */
}

void sideAuton(void) {

  printScreen("Running Auton");  

  Catapult.setStopping(brake);  
  Catapult.setMaxTorque(100, percent);
  Catapult.setVelocity(60, percent);
  Catapult.spin(forward);
  
  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);

  PStraight(15, 100);
  BackWingPneu.set(true);
  wait(0.75, seconds);
  Brain.Timer.clear();
  Drivetrain.drive(reverse);
  while (Brain.Timer.time(seconds) < 1) {
  }
  Drivetrain.stop();
  BackWingPneu.set(false);
  Catapult.stop();
  /*
  PStraight(24, 100);
  PRight(45, 2);
  Intake.spin(reverse);
  wait(0.5, seconds);
  Intake.stop();
  PStraight(-4, 100);
  PRight(225, 2);
  PStraightTime(1, -50);
  PStraight(8, 100);
  PLeft(180, 2);
  PStraight(31, 100);
  */
  wait(1, seconds);
  PLeft(160, 3);
  PStraight(6, 100);
  PLeft(135, 6);
  Intake.spin(reverse);
  PStraight(26, 100);
}

void sixBall() {
  Catapult.setStopping(brake);  
  Catapult.setMaxTorque(100, percent);
  Catapult.setVelocity(75, percent);
  
  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(100, percent);
  Intake.spin(forward);

  Intake.spin(forward);
  PStraight(5, 100);
}

void userControl(void) {

  leftMotorA.setStopping(brake);
  leftMotorB.setStopping(brake);
  leftMotorC.setStopping(brake);
  rightMotorA.setStopping(brake);
  rightMotorB.setStopping(brake);
  rightMotorC.setStopping(brake);  

  printScreen("Running Driver Control");  
    
  Controller1.ButtonL1.pressed(spinIntakeForward);
  Controller1.ButtonL1.released(stopIntake);

  Controller1.ButtonL2.pressed(spinIntakeReverse);
  Controller1.ButtonL2.released(stopIntake); 

  Controller1.ButtonR1.pressed(toggleFrontWings);
  Controller1.ButtonR2.pressed(toggleBackWings);
  
  Controller1.ButtonX.pressed(shootCatapult);
  Controller1.ButtonX.released(stopCatapult);

  Controller1.ButtonB.pressed(skillsCatapult);
  
  Controller1.ButtonRight.released(toggleEndgame);
   
  // place driver control in this while loop
  int driveSpeed = 1;
  double turnSpeed = 0.4;
  while (true) {
    if ((Controller1.Axis2.position() < 0 && Controller1.Axis3.position() > 0) || (Controller1.Axis2.position() > 0 && Controller1.Axis3.position() < 0)) {
      LeftDriveSmart.setVelocity(turnSpeed*Controller1.Axis3.position(), percent);
      RightDriveSmart.setVelocity(turnSpeed*Controller1.Axis2.position(), percent);
      leftMotorC.setVelocity(turnSpeed*Controller1.Axis3.position(), percent);
      rightMotorC.setVelocity(turnSpeed*Controller1.Axis2.position(), percent);
      LeftDriveSmart.spin(forward);
      RightDriveSmart.spin(forward);
      leftMotorC.spin(reverse);
      rightMotorC.spin(reverse);
    }
    else {
      LeftDriveSmart.setVelocity(driveSpeed*Controller1.Axis3.position(), percent);
      RightDriveSmart.setVelocity(driveSpeed*Controller1.Axis2.position(), percent);
      leftMotorC.setVelocity(driveSpeed*Controller1.Axis3.position(), percent);
      rightMotorC.setVelocity(driveSpeed*Controller1.Axis2.position(), percent);
      LeftDriveSmart.spin(forward);
      RightDriveSmart.spin(forward);
      leftMotorC.spin(reverse);
      rightMotorC.spin(reverse);
    }
    wait(5, msec);
  }
}

int Display() {
  while (true) {
    Brain.Screen.setFont(mono40);
    Brain.Screen.setPenColor(white);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Heading: %.0f", static_cast<float>(Drivetrain.heading()));
    Brain.Screen.newLine();
    wait(2, seconds);
  }
  return 0;
}

int main() {
  // create competition instance
  competition Competition;

  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(sideAuton);
  Competition.drivercontrol(userControl);

  task ws1(Display);

  // Run the pre-autonomous function.
  preAutonomous();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
