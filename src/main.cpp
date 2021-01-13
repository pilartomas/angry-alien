/*
 * Simple game using LCD and Joystick peripherals
 */

#include "Arduino.h"
#include "Game.hpp"

Game game;
// Display display;

void setup()
{
  // display.write(ALIEN);
  // display.write(DOWNWARD_SPIKE);
  // display.write(UPWARD_SPIKE);
}

void loop()
{
  game.run();
}