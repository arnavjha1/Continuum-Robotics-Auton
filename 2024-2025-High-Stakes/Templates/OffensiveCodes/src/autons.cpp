#include "vex.h"
int matchloadangle = -30;

void default_constants(){
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);
  chassis.set_drive_exit_conditions(1.5, 300, 800);
  chassis.set_turn_exit_conditions(1, 300, 1800);
  chassis.set_swing_exit_conditions(1, 300, 1000);
}

void odom_constants(){
  default_constants();
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
}

void regular(){
  int d = matchloadangle;
  chassis.drive_distance(-18, 30+d);
  chassis.set_drive_constants(11, 1, 0, 10, 0);
  chassis.drive_distance(-2.5, 30+d);
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  wait(0.1, seconds);
  MogoPneu.set(true);
  wait(0.2, seconds);
  Intake.spin(forward);
  wait(0.6, seconds);
  chassis.right_swing_to_angle(139+d);
  chassis.drive_distance(26, 139+d);
  //chassis.right_swing_to_angle(120+d);
  //chassis.set_drive_constants(11, 15, 0, 10, 0);
  //chassis.drive_distance(5, 120+d);
  //chassis.right_swing_to_angle(98+d);
  wait(0.5, seconds);
  //chassis.set_drive_constants(11, 20, 0, 10, 0);
  chassis.drive_distance(-10, 139+d);
  chassis.right_swing_to_angle(120+d);
  chassis.drive_distance(14, 120+d);
  wait(0.4, seconds);
  //Intake.stop();
  chassis.set_drive_constants(11, 1.5, 0, 10, 0);
  chassis.drive_distance(-18, 120+d);
  //chassis.right_swing_to_angle(115+d);
  //chassis.drive_distance(-15, 115+d);
  //chassis.right_swing_to_angle(180+d);
  chassis.set_drive_constants(11, 15, 0, 10, 0);
  chassis.left_swing_to_angle(70+d);
  //Intake.spin(forward);
  chassis.drive_distance(19, 70+d);
  wait(1.6, seconds);
  chassis.set_drive_constants(11, 3, 0, 10, 0);
  chassis.drive_distance(-30, 70+d);
}

void mirrored(){
  //Pre-auton
  int d = matchloadangle;
  
  //Auton goes here
   
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

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_point(0, 18, 90);
  chassis.holonomic_drive_to_point(18, 0, 180);
  chassis.holonomic_drive_to_point(0, 18, 270);
  chassis.holonomic_drive_to_point(0, 0, 0);
}