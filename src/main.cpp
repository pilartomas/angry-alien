/*
 * Simple game using LCD and Joystick peripherals
 */

#include "Arduino.h"
#include "Game.hpp"

Game game;

void setup()
{
}

void loop()
{
  game.run();
}