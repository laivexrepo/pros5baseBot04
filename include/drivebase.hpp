#ifndef DRIVE_BASE_H_
#define DRIVE_BASE_H_

#include "globals.hpp"

#define WHEEL_DIAM 7      // diameter in cm
#define WHEEL_BASE 38.5   // wheel base distance between center
                          // of two frontwheels in cm

void driveForDistance(float distance, int speed);  // drive a distance in cm at
                                                   // a given speed

#endif
