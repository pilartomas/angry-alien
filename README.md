# Angry Alien

Game where you take control of Angry Alien and attempt to survive for as long as possible. Avoid spikes and shoot skulls.

## Hardware requirements

- Arduino
- LCD 16x2 module with Hitachi HD44780 LCD controller
- Arduino Joystick module

## Instructions

1. Connect display and joystick to the arduino (see [Joystick.hpp](./include/Joystick.hpp) and [Display.hpp](./include/Display.hpp) for wiring instructions)
2. Install [Platformio IDE](https://platformio.org/platformio-ide)
3. Build & Upload the game
4. Follow the tutorial
5. Play the game
6. Holding the joystick pressed will skip the tutorial next time you reset the controller

## Architecture

Architecture is quite simple. We use `Joystick` class for reading the user input and `Display` class for the output to the LCD. Game itself consists of `Engine` class that implements the core functionality and `Game` class that puts all the aforementioned functionality together.
