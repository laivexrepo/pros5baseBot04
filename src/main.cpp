#include "main.h"
#include "portdef.hpp"		// portdef.hpp defines all the ports by name we use on the V5 brain
													// using a portdef.hpp file, and using the definitions set in their
													// as the paramenters when we need to specify a port in our code,
													// allows us very quickly to move things around and gives us one
													// place to look for all the ports and their assigned functions

#include "globals.hpp"		// ensure access to all global functions and variables
													// this goes hand in hand with globals.cpp

#include "drivebase.hpp"	// Include the drivebase functions for use, see drivebase.cpp
													// drivebase.hpp for definitions and descriptions

#include "autonomous.hpp"	// Include the autnomous functions, these contain the
													// the two autonomous routines one for 45sec and one for 2min
													// as coded in autonomous.cpp
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// While technicaly not needed it is a good practice to intialize the motors
	// and sensors during the intialization face of the program
	// We are using the green cartridge here - if they are changed the MOTOR_GEARSET
	// needs to be subsequently adjusted
	//             red    - 100RPM max  (MOTOR_GEARSET_36)
	//             green  - 200RPM      (MOTOR_GEARSET_18)
	//             blue   - 600RPM      (MOTOR_GEARSET_6)
	// Also notice the right_whell motor has the direction reversed, so in this case
	// if we give a command to move forward, the left motor runs clockwise and the
	// right motor counter clockwise - moving the robot forward.

	// gearset is set to the RED cartridge - you may need to change back to default of green
	// by changing MOTOR_GEARSET_36 to MOTOR_GEARSET_18
	pros::Motor left_wheel (LEFT_MOTOR_PORT, MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_DEGREES);
	pros::Motor right_wheel (RIGHT_MOTOR_PORT, MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// This section runs the fieldcontrol triggered autonomous code, which
	// code is defined in the functions located in autonomous.cpp (autonomous.hpp)
	// call the appropriate one here depending on what your bot will be doing.

  // comment / uncomment the one to use
	auto45sec();				// 45 second autonomous
	//autoSkill();				// 2 minute autonomous code
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	// Call one of the two autonomous functions here for testing
	// comment/uncomment one of thefunctions

	auto45sec();					// 45 sec autonomous routine

	//autoSkill();					// 2minute autonomous routine
}
