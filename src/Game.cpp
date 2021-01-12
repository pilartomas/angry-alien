#include "Game.hpp"

#include <util/delay.h>
#include <stdlib.h>

void Game::run()
{
    wait();
    render();
}

// Actively waits INTERVAL_MILLIS but also listens to an action
void Game::wait()
{
    auto countdown = INTERVAL_MILLIS;
    while (countdown > 0)
    {
        _delay_ms(1);
        countdown--;
        // joystick can be in many states but we want only one action
        if (joystick.isPressed())
            engine.toggleStatus();
        else if (joystick.isUp())
            engine.step(UP);
        else if (joystick.isDown())
            engine.step(DOWN);
        else if (joystick.isLeft())
            engine.step(LEFT);
        else if (joystick.isRight())
            engine.step(RIGHT);
        else
            continue;
        break;
    }
    if (countdown == 0)
        engine.step(WAIT);
    // if we broke due to an action, wait out the rest
    while (countdown > 0)
    {
        _delay_ms(1);
        countdown--;
    }
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