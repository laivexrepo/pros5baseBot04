// ------- drivebase.cpp ---------------------------------------------------------
//
// Use drivebase.cpp together with drivebase.hpp to define all drivebase related movement
// functions, which should be available/accessible in autonomous and opcontrol code.
//
// for example setup a function called driveForDistance() which takes two inputs,
// by declaring the function in drivebase.hpp as well, it will become generally
// available - ensure you include #include "drivebase.hpp" in the relevant source (.cpp) files

#include "main.h"
#include "globals.hpp"
#include "portdef.hpp"
#include "drivebase.hpp"

// Below is a generic drive for distance function, which can be called anywhere
// as long as drivebase.hpp is included.  Any new function you define here MUST be
// declared in drivebase.hpp for general use.

void driveForDistance(float distance, int speed) {
  // function drives robot for set distance where distance is
  // given in cm.  A negative number makes the robot drive backwards.
  // distance -- distance in cm
  // speed    -- speed in RPM -- please note cartridge installed for range
  //             red    - 100RPM max  (MOTOR_GEARSET_36)
  //             green  - 200RPM      (MOTOR_GEARSET_18)
  //             blue   - 600RPM      (MOTOR_GEARSET_6)

  // Imagine a wheel of diameter 10cm - this means it's circumfrence is equal to:
  // circum = 3.14 * 10cm = 31.4cm
  // This means that for every 360 degree of axel turn the robot travels 31.4cm
  // This means that for 1degree of rotation this is: (3.14 * 10) / 360 = 0.08722cm of travel
  // So if we know that then if we want to travel for a given distance in cm, we can calculate
  // the number of encoder degrees we need to move by taking
  // Numb of Degrees to travel =  distance to travel / distance for 1 degree

  // We use drivebase.hpp to set the wheel diameter
  float degreesTravel = (distance / (3.14 * WHEEL_DIAM)) * 360;
  // set the "window" for which we need to encoder to reach and stop movement
  float degreesTravelAbs = fabsf(degreesTravel);        // we are doing absolute values
  float minTarget = degreesTravelAbs -5;                // we can also go backwards by
  float maxTarget = degreesTravelAbs +5;                // giving a -distance as input!

  left_wheel.tare_position();       // ensure encoders are reset before
  right_wheel.tare_position();      // movement.
  left_wheel.move_absolute(degreesTravel, speed);
  right_wheel.move_absolute(degreesTravel, speed);

  if(DEBUG){
     std::cout << "\ndriveForDistance -- distance: " << distance << " speed: " << speed << "\n";
     std::cout << "Degrees to travel: " << degreesTravel << "\n";
     std::cout << "minTarget: " << minTarget << " maxTarget: " << maxTarget << "\n";
  }
  // We need to make sure motors reach there target +- 5 degrees.
  while (!((fabs(left_wheel.get_position()) < (maxTarget)) && (fabs(left_wheel.get_position()) > minTarget))) {
    pros::delay(2);
  }
  if(DEBUG) {
    std::cout << "Encoder Left: " << left_wheel.get_position() << " Right: " << right_wheel.get_position() << "\n";
  }
  // we will stop the motors
  left_wheel.move_velocity(0);
  right_wheel.move_velocity(0);
}
