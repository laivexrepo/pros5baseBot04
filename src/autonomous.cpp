// ------- autonomous.cpp ---------------------------------------------------------
//
// Use autonomous.cpp together with autonomous.hpp to define all autonomous related movement
// functions,.
//
// Forexample we declare two functions here: auto45sec() - for 45sec autonomous routine and
// autoSkill() - for the full 2min skill (autonomous) only robot operations.  Each of these
// functiosn contain all the code which is needed to accomplish either the 45sec or full 2min
// autonomous run. Then by calling either one of these functions in the autonomous() section
// of main.cpp will ensure the proper autonomous would be run.

#include "main.h"
#include "globals.hpp"
#include "portdef.hpp"
#include "drivebase.hpp"        // drivebase functions including drivebase task definition
#include "intake.hpp"           // intake functions including intake task definition
#include "autonomous.hpp"
#include "tasks.hpp"            // ensure access to tasks definition for our code

// --------------------- autonomous skill code ---------------------------------------
// This function is supposed to be called in the autonomous() portion of the main.cpp code
// when running just a two minute long autonomous portion of a competition

void autoSkill() {
  // This is the 2 minute autonomous function code section, call
  // this function if you need to run the full 2 minute autonomous.
  motorMaxSpeed = 25;			// Lets set the max speed of movement, remember it is
                          // a glbal variabel see globals.cpp/globals.hpp


  // Now lets move the robot forward for a bit.  We use relative movement here, so we
  // move encoder unit increments no matter what are current encoder count is, as
  // we specified E_MOTOR_ENCODER_DEGREES in motor setup we will rotate the motor 1000 degrees
  // See here for more detail: https://pros.cs.purdue.edu/v5/api/cpp/motors.html#move-relative

  // We should ensure that the eoncoders start at 0, this makes it easier to visualize and ensure
  // motors move for the given requested distance
  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.

  right_wheel.move_relative(1000, motorMaxSpeed);		// Move forward for 1000 encoder units
  left_wheel.move_relative(1000, motorMaxSpeed);
  // Important to understnad - we need to let the motor run it's course and ensure that it gets within
  // +-5  if we do not do that it would randomly either directly move on to the next movement or
  // never execute what comes next, as it will NEVER precisely reach the requested encoder units
  while (!((left_wheel.get_position() < 1005) && (left_wheel.get_position() > 995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  // Lets print out the encoder values after the movement is completed, notice that it will have a
  // value whihc is within +-5 units of request, likely slight below the requested vaule
  // To view this output ensure hte V5 is connected via USB cable to your computer
  // and open the Consoel Terminal (menu PROS -> Open Terminal)
  std::cout << "After forward: Encoder left: " << left_wheel.get_position() << "\n";

  // lets make a turn to the left, meaning we are only going to spin the left motor
  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.

  // let set a new motorMaxSpeed and lets check if it is allowed, if not we set it to the
  // maximum allowable speed.
  motorMaxSpeed = 300;
  if(motorMaxSpeed > maxAllowedSpeed) {
    // Oops we are exceeding maximum value.....
    motorMaxSpeed = maxAllowedSpeed;							// setting to the max maxAllowedSpeed
  }
  // for fun lets print what the speed is
  std::cout << "Motospeed is set to: " << motorMaxSpeed << "\n";

  left_wheel.move_relative(1000, motorMaxSpeed);
  while (!((left_wheel.get_position() < 1005) && (left_wheel.get_position() > 995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  std::cout << "After turn: Encoder left: " << left_wheel.get_position() << "\n";

  // Lest drive backwards for a movement, we are going to give it negative encoder counts
  // This also means our while wait loop needs to change to reflect in thsi case -1005 and -995
  // and the > and < signs flip!

  // Lets set out speed to the default
  motorMaxSpeed = motorDefaultSpeed;									// comes from globals.cpp

  // for fun lets print what the speed is
  std::cout << "Motospeed is set to: " << motorMaxSpeed << "\n";

  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.

  right_wheel.move_relative(-1000, motorMaxSpeed);		// Move forward for 1000 encoder units
  left_wheel.move_relative(-1000, motorMaxSpeed);

  while (!((left_wheel.get_position() > -1005) && (left_wheel.get_position() < -995))) {
    // Continue running this loop as long as the motor is not within +-5 units of its goal
    pros::delay(2);
  }
  std::cout << "After drive Backwards: Encoder left: " << left_wheel.get_position() << "\n";

  // We could ensure that robot is completely stopped by issuing the following commands to the motors:
  left_wheel.move_velocity(0);
  right_wheel.move_velocity(0);
}

// ------------------ 45 sec autonomous routine -------------------------------------------
// This autonomous code is supposed to be called in autonomous() section of main.cpp as part
// of the autonomous + operator control competition portion

void auto45sec() {
  // This is the 45 sec autonomous code function, call
  // this function when you need to run the 45 sec autonomous.

  // Lets use our new drivebase.cpp defined function to drive for a given distance
	// Lets drive for 100cm - can you predict the encoder values?
	if(DEBUG) {std::cout << "Drivebase function: 100cm and speed 65 will be called \n"; }
	driveForDistance(100, 65);
	std::cout << "Finished drive for distance of 100cm at 65RPM speed \n";

  // Lets drive backwards for 25cm, at full speed (100rpm)
  if(DEBUG) {std::cout << "Drivebase function: -25cm and speed 100 will be called \n"; }
  driveForDistance(-25, 100);
  std::cout << "Finished drive for distance of -25cm (backwards) at 100RPM speed \n";

}

// -------------------- autonomous task based code sample -----------------------------------
// This example function runs an autonomous routine which uses tasks to allow for the
// ´parallel´functionailty between two or more subsystems

void autoTask(){
  // Since we will be using tasks in this sample code, we first need to ensure all
  // tasks are stopped - the only running task should be the display task and the odometer
  // tasks which will stay active and show the current running tasks counter and odometer
  // readings to the console
  killTasks();

  // reset the odometers -- we communicate via global to the odometer task
  odomResetFlag = true;

  runIntakeNow = false;     // ensure intake task does not start intake mechanism
                            // until asked todo so!

  // Lets start a intake task here
	intake = pros::Task (intakeTaskFnc, (void*)"PROS", TASK_PRIORITY_DEFAULT,
								TASK_STACK_DEPTH_DEFAULT, "Intake Task"); //starts the task
	// no need to provide any other parameters

  // Lets start a intake task here
	drive = pros::Task (driveTaskFnc, (void*)"PROS", TASK_PRIORITY_DEFAULT,
								TASK_STACK_DEPTH_DEFAULT, "Drive Task"); //starts the task
	// no need to provide any other parameters

  // both tasks run until autonomous is ended or if a task has finished - in our
  // example case the drive task is the controlling task - it syncrhonizes with the
  // intake task via the global intakeRunNow and intakeReverse global booleans.

}
