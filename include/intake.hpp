#ifndef INTAKE_H_
#define INTAKE_H_

void runIntake(int speed);          // control the intake:
                                    // speed = 0 - stopped
                                    // speed +- value run at given speed

extern void intakeTaskFnc(void* ignore);  // control intake via task

#endif
