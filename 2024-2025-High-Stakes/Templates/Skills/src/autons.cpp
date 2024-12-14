#include "vex.h"
int matchloadangle = 0;
int m = 1;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 1800);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

int LiftArm() {
  Arm.spinFor(reverse, 0.2, turns);
  return 0;
}

void SpedUp(){
  default_constants();
  chassis.set_heading(180);
  chassis.arm_to_angle(60);
  chassis.drive_distance(6.5);
  chassis.arm_to_angle(20);
  Arm.stop();
  chassis.drive_distance(-11.5);
  chassis.turn_to_angle(270);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-23);
  Intake.spin(forward);
  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(25);
  chassis.turn_to_angle(90);
  chassis.drive_distance(25);
  chassis.turn_to_angle(180);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.drive_distance(35);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  wait(0.5, seconds);
  chassis.drive_distance(-25);
  chassis.turn_to_angle(140);
  chassis.drive_distance(15);
  chassis.turn_to_angle(335);
  chassis.drive_distance(-10);
  MogoPneu.set(false);
  Intake.stop();
  chassis.drive_distance(5.5);
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.set_turn_exit_conditions(0.5, 300, 5000);
  chassis.turn_to_angle(88);
  chassis.set_heading(90);
  chassis.drive_distance(-80, 90);
  MogoPneu.set(true);
  Intake.spin(forward);
  wait(0.3, seconds);
  chassis.turn_to_angle(0);
  default_constants();
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  chassis.drive_distance(24);
  chassis.turn_to_angle(270);
  chassis.drive_distance(25);
  chassis.turn_to_angle(180);
  chassis.set_drive_constants(4, 1.5, 0, 10, 0);
  chassis.drive_distance(35);
  chassis.set_drive_constants(6, 1.5, 0, 10, 0);
  wait(0.5, seconds);
  chassis.drive_distance(-25);
  chassis.turn_to_angle(220);
  chassis.drive_distance(15);
  chassis.turn_to_angle(25);
  chassis.drive_distance(-10);
  MogoPneu.set(false);
  Intake.stop();
  chassis.drive_distance(6);
}

void DriveStraight() {
  default_constants();
  chassis.set_drive_constants(3, 1.5, 0, 10, 0);
  chassis.drive_distance(-75);
}

void Auton26Points(){
  vex::task t(LiftArm);
  chassis.set_drive_constants(4, 1.5, 0, 15, 0);
  chassis.drive_distance(13);  
  chassis.turn_to_angle(-90);
  chassis.drive_distance(-14);
  chassis.set_drive_constants(2, 1.5, 0, 15, 0);
  chassis.drive_distance(-12);
  MogoPneu.set(true);
  wait(0.3, seconds);
  Intake.spin(forward);
  wait(0.3, seconds);
  chassis.set_drive_constants(5, 1.5, 0, 15, 0);
  chassis.turn_to_angle(17);
  wait(0.2, seconds);
  chassis.drive_distance(30);
  wait(0.2, seconds);
  chassis.turn_to_angle(90);
  wait(0.2, seconds);
  chassis.drive_distance(28);
  wait(0.2, seconds);
  chassis.turn_to_angle(180);
  wait(0.2, seconds);
  chassis.drive_distance(19);
  //wait(0.5, seconds);
  chassis.drive_distance(13);  
  wait(0.2, seconds);
  chassis.drive_distance(-23);
  wait(0.2, seconds);
  chassis.turn_to_angle(140);
  wait(0.3, seconds);
  chassis.drive_distance(12);  
  wait(0.5, seconds);
  chassis.turn_to_angle(-10);
  wait(0.2, seconds);
  chassis.drive_distance(-15);
  Intake.spinFor(reverse, 2, turns, false);
  wait(0.2, seconds);
  Intake.stop();
  MogoPneu.set(false);
  wait(0.2, seconds);
  chassis.drive_distance(7.5);
  wait(0.2, seconds);
  chassis.turn_to_angle(-90);
  wait(0.2, seconds);
  chassis.set_drive_constants(4, 1.5, 0, 15, 0);
  chassis.drive_distance(20);
  chassis.drive_distance(20);
  chassis.drive_distance(21);
  chassis.turn_to_angle(90);
  wait(0.2, seconds);
  chassis.set_drive_constants(2, 1.5, 0, 15, 0);
  chassis.drive_distance(-44);
  wait(0.2, seconds);
  MogoPneu.set(true);
  wait(0.3, seconds);
  chassis.set_drive_constants(5, 1.5, 0, 15, 0);
  Intake.spin(forward);
  chassis.turn_to_angle(-25);
  wait(0.2, seconds);
  chassis.drive_distance(30);
  wait(0.2, seconds);
  chassis.turn_to_angle(-52);
  wait(0.2, seconds);
  chassis.drive_distance(20);
  chassis.drive_distance(20);
  wait(0.2, seconds);
  chassis.drive_distance(-12);
  wait(0.2, seconds);
  chassis.turn_to_angle(180);
  wait(0.2, seconds);
  chassis.drive_distance(20);
  wait(0.3, seconds);
  chassis.drive_distance(15);
  wait(0.3, seconds);
  chassis.drive_distance(15);
  wait(1, seconds);
  chassis.drive_distance(-15);
  chassis.drive_distance(-10);
  wait(0.2, seconds);
  chassis.turn_to_angle(-145);
  wait(0.2, seconds);
  chassis.drive_distance(20);
  wait(0.5, seconds);
  chassis.drive_distance(-5);
  wait(0.5, seconds);
  chassis.turn_to_angle(-90);
  wait(0.2, seconds);
  chassis.turn_to_angle(30);
  wait(0.2, seconds);
  chassis.drive_distance(-10);
  wait(0.5, seconds);
  Intake.spinFor(reverse, 2, turns, false);
  wait(0.2, seconds);
  Intake.stop();
  MogoPneu.set(false);
  wait(0.2, seconds);
}

//The following codes are test codes, avoid editing!
void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(0,50, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(0,70, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(0,90, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(0,110, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(0,130, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}