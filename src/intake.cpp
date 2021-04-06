// ------- intake.cpp ---------------------------------------------------------
//
// Use intake.cpp together with intake.hpp to define all intake related actions /
// functions, which should be available/accessible in autonomous and opcontrol code.
//
// For example setup a function called intakeRun() which takes a single input
// by declaring the function in intake.hpp as well, it will become generally
// available - ensure you include #include "intake.hpp" in the relevant source (.cpp) files

#include "main.h"
#include "globals.hpp"
#include "portdef.hpp"
#include "intake.hpp"
#include "tasks.hpp"

// ------------------------------- intakeRun function ---------------------------------
// control the running of the intake includign stopping and direction at given RPM controlled
// by build in motor PID

void runIntake(int speed){
  // int speed -  control RPM of the intake System, if called with speed = 0
  //              the intake is stopped, when called with a a negtive value, -100
  //              the intake will run counter clockwise at 100RPM, when called with 50
  //              the intake will run at 50RPM clockwise

  if(speed == 0){
    // stop the intake
    intake_motor.move_velocity(0);
  } else {
    // run intake at given RPM (- equals counter clockwise)
    intake_motor.move_velocity(speed);
  }
}

// ----------------------- autonomous mode intake task ---------------------------------------
// The function intakeTaskFnc() will be called by the autoTask() function and ontrols the
// intake via  a seperate task during the autonomous period.

void intakeTaskFnc(void* ignore) {
    //the void* is there to provide a way to pass a
    //generic value or structure to the task if needed
    //pros needs this parameter in your function even if you don't use it

    // Run task permanently until removed from rtos task list, ensure no starvation
    // of CPU to occur

    int speed = 75;                     // clockwise speed in RPM
    int reverseSpeed = -50;             // counter clockwise speed in RPM

    while (true) {
      if(runIntakeNow) {                // runIntakeNow is global flag for inter
                                        // task communication
        if(DEBUG) { std::cout << "Running Intake Task \n";}
        // we are asked to run the intake - now what direction?
        if(reverseIntake){              // reverseIntake is a global flag for
                                        // inter task communication
          // run counter clockwise
          if(DEBUG) { std::cout << "Reversing directions \n";}

          runIntake(reverseSpeed);    // counter clockwise at reverseSpeed
        } else {
          runIntake(speed);           // clockwise at speed
        }
      } else {
        runIntake(0);                 // stop intake
        if(DEBUG) { std::cout << "Stopped intake Task \n";}
      }
      pros::delay(20);                // ensure task will not starve processor
    }
}
