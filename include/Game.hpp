#include "Joystick.hpp"
#include "Display.hpp"
#include "Engine.hpp"

#define HEIGHT 2
#define WIDTH 16

#define JOYSTICK_SENSITIVITY 250

struct Game
{
public:
    void run();

private:
    unsigned int INTERVAL_MILLIS = 500;

    Joystick joystick{JOYSTICK_SENSITIVITY};
    Display lcd;
    Engine<HEIGHT, WIDTH> engine;

    void acceptActions();
    void forwardGame();

    void render();
    void showScore();
    void renderState();
    void renderRow(const Line row);
};