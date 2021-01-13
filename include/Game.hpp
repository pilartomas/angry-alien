#include "Joystick.hpp"
#include "Display.hpp"
#include "Engine.hpp"

struct Game
{
public:
    void run();

private:
    unsigned int INTERVAL_MILLIS = 500;

    Joystick joystick;
    Display lcd;
    Engine engine;

    void acceptActions();
    void forwardGame();

    void render();
    void showScore();
    void renderState();
    void renderRow(const Line row);
};