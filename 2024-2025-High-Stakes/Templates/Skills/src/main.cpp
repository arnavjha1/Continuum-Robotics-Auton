#include "vex.h"
bool runningSkills = false;
//Part of the code below (mainly the drivetrain constrictors) is used from the LemLib drive template, which is why you will notice a unique drivetrain setup
//This drivetrain setup is specifically made to allow the most efficient drive possible, using LemLib's battery saving technique while still providing high strength
//The drivetrain will stay on Eco mode for most of the High Stakes challenge

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// DigitalOutF          digital_out   F               
// LeftFront            motor         1               
// LeftBack             motor         12              
// RightFront           motor         8               
// RightBack            motor         20              
// Left6th              motor         14              
// Right6th             motor         18              
// Inertial13           inertial      13              
// WingPneu             digital_out   D               
// IntakePneu           digital_out   E               
// LimitSwitchC         limit         C               
// Catapult             motor         9               
// Intake               motor         11              
// MotorGroup17         motor_group   17, 16          
// ---- END VEXCODE CONFIGURED DEVICES ----

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                              LemLib Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".


//Left Motors:
motor_group(LeftFront, LeftBack, Left6th),

//Right Motors:
motor_group(RightFront, RightBack, Right6th),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT13,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.75,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT1,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
3,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
1,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

//Automatic Drivetrain Selector
motor_group Drivetrain = motor_group(LeftBack, LeftFront, RightFront, RightBack, Right6th, Left6th);

int current_auton_selection = 0;
bool auto_started = false;

void pre_auton(void) {
  //DO NOT REMOVE THE FOLLOWING TWO FUNCTIONS! The entire code will break!
  vexcodeInit();
  default_constants();

  Drivetrain.setStopping(coast);
  Inertial13.calibrate();
  
  Arm.setStopping(hold);
  Arm.setMaxTorque(100, percent);
  Arm.setVelocity(50, percent);

  IntakePneu.set(false);
  HangPneu.set(true);

  Intake.setStopping(brake);
  Intake.setMaxTorque(100, percent);
  Intake.setVelocity(100, percent);

  LeftFront.setMaxTorque(100, percent);
  LeftBack.setMaxTorque(100, percent);
  Left6th.setMaxTorque(100, percent);
  RightBack.setMaxTorque(100, percent);
  RightFront.setMaxTorque(100, percent);
  Right6th.setMaxTorque(100, percent);

  LeftFront.setVelocity(100, percent);
  LeftBack.setVelocity(100, percent);
  Left6th.setVelocity(100, percent);
  RightFront.setVelocity(100, percent);
  RightBack.setVelocity(100, percent);
  Right6th.setVelocity(100, percent);
  Intake.setVelocity(100.0, percent);
  while(auto_started == false){            //Changing the names below will only change their names on the
    Brain.Screen.clearScreen();  //brain screen for auton selection.
    switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
      case 0:      
        Brain.Screen.printAt(50, 50, "Red ");
        controller(primary).Screen.print("Red ");
        break;
      case 1:
        Brain.Screen.printAt(50, 50, "Blue");
        controller(primary).Screen.print("Blue");
        break;
     /* case 2:
        Brain.Screen.printAt(50, 50, "Turn Test");
        break;
      case 3:
        Brain.Screen.printAt(50, 50, "Swing Test");
        break;
      case 4:
        Brain.Screen.printAt(50, 50, "Full Test");
        break;
      case 5:
        Brain.Screen.printAt(50, 50, "Odom Test");
        break;
      case 6:
        Brain.Screen.printAt(50, 50, "Tank Odom Test");
        break;
      case 7:
        Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
        break;*/
    }
    if(LimitSwitchC.pressing()){
      while(LimitSwitchC.pressing()){}
      current_auton_selection = 1-current_auton_selection;
    }
    task::sleep(10);
  }
}

void autonomous(void) {
  auto_started = true;
  switch(current_auton_selection){  
    case 0:
      regular(); //This is the default auton, if you don't select from the brain.
      break;        //Change these to be your own auton functions in order to use the auton selector.
    case 1:         //Tap the screen to cycle through autons.
      mirrored();
      break;
    /*case 2:
      turn_test();
      break;
    case 3:
      swing_test();
      break;
    case 4:
      full_test();
      break;
    case 5:
      odom_test();
      break;
    case 6:
      tank_odom_test();
      break;
    case 7:
      holonomic_odom_test();
      break;*/
 }
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
bool mobilePneu = false;
bool intakePneu = false;

void loadArm() {

  while (true) {
    if (DistSensor.objectDistance(inches) < 1) {
      Intake.spinFor(reverse, 10, turns);
      break;
    }
    else  {
      Intake.spin(forward);
    }

    wait(0.02, seconds);
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

void toggleIntakePneuPos() {
  if (intakePneu) {
    IntakePneu.set(false);
    intakePneu = false;
  }
  else {
    IntakePneu.set(true);
    intakePneu = true;
  }  
}

void triggerMogoMech() {
  if (mobilePneu) {
    MogoPneu.set(false);
    mobilePneu = false;
  }
  else {
    MogoPneu.set(true);
    mobilePneu = true;
  }
}

bool hangPneuPos = false;

void triggerHangMech() {
  hangPneuPos = !hangPneuPos;
  HangPneu.set(hangPneuPos);
}

void moveArmUp() {
  Arm.spin(reverse);
}

void moveArmDown() {
  Arm.spin(forward);
}

void stopArm() {
  Arm.stop();
}

void usercontrol(void) {
    if(runningSkills){
      macro();
    }
    Arm.setStopping(brake);

    controller(primary).ButtonL2.pressed(spinIntakeReverse); 
    controller(primary).ButtonL2.released(stopIntake); 

    controller(primary).ButtonL1.pressed(spinIntakeForward);
    controller(primary).ButtonL1.released(stopIntake); 

    controller(primary).ButtonR1.pressed(triggerMogoMech);
    controller(primary).ButtonR2.pressed(triggerHangMech);

    controller(primary).ButtonY.pressed(moveArmUp);
    controller(primary).ButtonY.released(stopArm);
    controller(primary).ButtonRight.pressed(moveArmDown);
    controller(primary).ButtonRight.released(stopArm);

    controller(primary).ButtonB.pressed(loadArm);
    controller(primary).ButtonB.released(stopIntake);

  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    //Replace this line with chassis.control_tank(); for tank drive 
    //or chassis.control_holonomic(); for holo drive.
    chassis.control_tank();

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}