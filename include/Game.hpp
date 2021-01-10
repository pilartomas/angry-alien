#include "Joystick.hpp"
#include "Display.hpp"
#include "Engine.hpp"

struct Game
{
public:
    void run();

private:
    Joystick joystick;
    Display lcd;
    Engine engine;

    void action();
    void render();
    void showScore();
    void renderState();
};