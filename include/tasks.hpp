#ifndef TASKS_H_
#define TASKS_H_

// task variables
extern pros::task_t intake;
extern pros::task_t drive;
extern pros::task_t odom;
extern pros::task_t display;

// task specific managment functions
extern void killTasks();            // kill all running tasks
extern void displayTaskFnc(void* ignore);   // display counter of all running tasks
extern void odomTaskFnc(void* ignore);      // odometer task 

// task global variables used to synchronize betwen tasks
extern bool runIntake;              // stop / start the intake conveyer
extern bool runTaskIntake;

extern bool odomResetFlag;

#endif
