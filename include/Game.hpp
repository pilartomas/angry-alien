#include "Joystick.hpp"
#include "Display.hpp"
#include "Engine.hpp"

#define JOYSTICK_SENSITIVITY 250

struct Game
{
public:
    void run();

private:
    unsigned int INTERVAL_MILLIS = 500;

    Joystick joystick{JOYSTICK_SENSITIVITY};
    Display lcd;
    Engine<DISPLAY_HEIGHT, DISPLAY_WIDTH> engine;

    void acceptActions();
    void forwardGame();

    void render();
    void showScore();
    void renderState();
    void renderRow(unsigned int row);
};