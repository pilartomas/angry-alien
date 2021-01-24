#include "Joystick.hpp"
#include "Display.hpp"
#include "Engine.hpp"

class Game
{
public:
    /*
     * joystickSensitivity - number between 0 and 512 (excluded)
     */
    Game(unsigned int joystickSensitivity = 250);

    /* Runs the game indefinitely, never returns
     *
     * stepPeriod - roughly how much milliseconds should one step take
     */
    void run(unsigned int stepPeriod = 500);

private:
    Joystick joystick;
    Display lcd;
    Engine<DISPLAY_HEIGHT, DISPLAY_WIDTH> engine;

    void tutorial();
    void acceptActions(unsigned int stepPeriod);
    void forwardGame();

    void render();
    void showScore();
    void renderState();
    void renderRow(unsigned int row);
};