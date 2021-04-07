#include "main.h"
#include "portdef.hpp"
#include "globals.hpp"
#include "pros/apix.h"								// we need the advanced API header
#include "pros/rtos.h"

pros::task_t intake = (pros::task_t)NULL;
pros::task_t drive = (pros::task_t)NULL;
pros::task_t odom = (pros::task_t)NULL;
pros::task_t display = (pros::task_t)NULL;

// task inter communication variables (globals)
bool odomResetFlag = false;       // reset reporting odometres to 0
bool runIntakeNow = false;        // stop / start the intake mechanism
bool reverseIntake = false;       // reverse direction of intake mechanism

/*----------------------------------------------------------------------------*/
// task we keep running all the time to show the number of active rtos tasks
//
void displayTaskFnc(void* ignore) {
    //the void* is there to provide a way to pass a
    //generic value or structure to the task if needed
    //pros needs this parameter in your function even if you don't use it
    if(DEBUG) { std::cout << "Starting display task \n"; }

    pros::lcd::initialize();          // Initialize the LCD display
    std::uint32_t now = pros::millis();   // time stamp in milli sec
    while(true) {
        pros::lcd::print(1, "Task Count %3d", pros::Task::get_count() );
        if(DEBUG) { std::cout << "Task Count: " << pros::Task::get_count() << "\n"; }
        pros::Task::delay_until(&now, 100);     // ensure consitent 100ms (10Hz cycle)
    }
}

/*----------------------------------------------------------------------------*/
// task we keep running all the time to report the odom difference between
// the left and right wheel
//
void odomTaskFnc(void* ignore) {
    //the void* is there to provide a way to pass a
    //generic value or structure to the task if needed
    //pros needs this parameter in your function even if you don't use it

    // lets insure the right odometer is reversed first
    if(DEBUG){ std::cout << "Right odom reversed? " << right_odom.get_reversed() << "\n"; }

    if(right_odom.get_reversed() > 0){
      right_odom.set_reversed(true);
    }

    std::uint32_t now = pros::millis();   // time stamp in milli sec
    while(true){
       if(odomResetFlag){
         // requested odometer odometer resets to 0
         left_odom.reset_position();
         right_odom.reset_position();
       }

       // get the left and right odom and show the difference
       int odom_diff = left_odom.get_position() - right_odom.get_position();
       std::cout << "Odom drift: " << odom_diff << "\n";
       pros::Task::delay_until(&now, 50);     // ensure consitent 50ms (20Hz cycle)
    }
}

/*----------------------------------------------------------------------------*/
// Function providing ability to kill all tasks accept the display task
//
void killTasks() {
	// ability to kill running tasks // tasks should in general be killed between
	// competition stage state changes
	if(intake) {                         // intake task
  	pros::Task(intake).remove();
	  intake = (pros::task_t)NULL;
  }
	if(drive) {                          // drive task
		pros::Task(drive).remove();
		drive = (pros::task_t)NULL;
	}
  // right now we are running the odom task always
  //if(odom) {                           // odomoter task
  //  pros::Task(odom).remove();
  //  odom = (pros::task_t)NULL;
  //}
  pros::delay(20);                    // lets give it a bit of time to complete
}
