#include "Game.hpp"

#include <util/delay.h>
#include <stdlib.h>

void Game::run()
{
    while (true)
    {
        acceptActions();
        forwardGame();
    }
}

#define ACTION_PAUSE_MILLIS 100

void Game::acceptActions()
{
    auto countdown = INTERVAL_MILLIS / ACTION_PAUSE_MILLIS;
    while (countdown > 0)
    {
        _delay_ms(ACTION_PAUSE_MILLIS);
        countdown--;
        // joystick can be in many states but we want only one action
        if (joystick.isPressed() && engine.status != RUNNING)
            engine.reset();
        else if (joystick.isUp())
            engine.action(UP);
        else if (joystick.isDown())
            engine.action(DOWN);
        else if (joystick.isLeft())
            engine.action(LEFT);
        else if (joystick.isRight())
            engine.action(RIGHT);
        else
            continue;
        render(); // some action have been taken, need to re-render
    }
}

void Game::forwardGame()
{
    engine.step();
    render();
}

void Game::render()
{
    switch (engine.status)
    {
    case FINISHED:
        showScore();
        break;
    default:
        renderState();
        break;
    }
}

void Game::showScore()
{
    char buffer[6];
    lcd.clear();
    lcd.start(FIRST);
    lcd.print("Score: ");
    lcd.print(itoa(engine.score, buffer, 10));
    lcd.start(SECOND);
    lcd.print("Press to restart");
}

void Game::renderState()
{
    lcd.clear();
    for (size_t j = 0; j < engine.HEIGHT; ++j)
    {
        if (j == 1)
            lcd.start(SECOND);
        for (size_t i = 0; i < engine.WIDTH; ++i)
        {
            switch (engine.state[j][i])
            {
            case AGENT:
                lcd.write('A');
                break;
            case SPIKE:
                lcd.write('S');
                break;
            case EMPTY:
                lcd.write(' ');
                break;
            }
        }
    }
}