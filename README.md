# pros5baseBot03
Basic two motor bot

This is a basic two motor based sample project to show how to setup a basic PROS program, this example shows the use of basic include files for general parameter settings.

In this example the autonomous code is moved to a code file autonomous.cpp / autonomous.hpp and facilitates the use of different autonomous length functions.  In this case two are defined, but the sky is the limit.

auto45sec() function is intended to hold the code to operate your bot for 45sec autonomous section of the competition. In here you should write all the code need to operate the bot for that period.  Then call this function in main.cpp in the void autonomous() section, and when the field control system triggers autonomous mode it will run the so defined 45sec routine you wrote.

autoSkill() function is intended to hold the code for the full 2 minute autonomous part of the game.  Again by calling this function in main.cpp in the autonomous() section, your bot would run your planned 2 minute autonomous code when triggered by the field control system.

You can write of course various versions of these functions for testing and just ensure you define them in autonomous.cpp / autonomous.hpp and then they are subsequently available for testing in your program. 
