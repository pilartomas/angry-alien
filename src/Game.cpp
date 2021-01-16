#include "Game.hpp"

#include <util/delay.h>
#include <stdlib.h>

Game::Game(unsigned int joystickSensitivity) : joystick(joystickSensitivity) {}

void Game::run(unsigned int stepPeriod)
{
    while (true)
    {
        acceptActions(stepPeriod);
        forwardGame();
    }
}

#define ACTION_PAUSE_MILLIS 100

void Game::acceptActions(unsigned int stepPeriod)
{
    auto countdown = stepPeriod / ACTION_PAUSE_MILLIS;
    while (countdown > 0)
    {
        _delay_ms(ACTION_PAUSE_MILLIS);
        countdown--;
        // joystick can be in many states but we want only one action
        if (joystick.isPressed() && engine.getStatus() != Status::RUNNING)
            engine.reset();
        else if (joystick.isUp())
            engine.action(Move::UP);
        else if (joystick.isDown())
            engine.action(Move::DOWN);
        else if (joystick.isLeft())
            engine.action(Move::LEFT);
        else if (joystick.isRight())
            engine.action(Move::RIGHT);
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
    switch (engine.getStatus())
    {
    case Status::FINISHED:
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
    lcd.start(0);
    lcd.print("Score: ");
    lcd.print(itoa(engine.getScore(), buffer, 10));
    lcd.start(1);
    lcd.print("Press to restart");
}

void Game::renderState()
{
    lcd.clear();
    renderRow(0);
    renderRow(1);
}

void Game::renderRow(unsigned int row)
{
    lcd.start(row);
    for (size_t i = 0; i < DISPLAY_WIDTH; ++i)
    {
        switch (engine.getState(row, i))
        {
        case LocationType::AGENT:
            lcd.write(ALIEN);
            break;
        case LocationType::SPIKE:
            if (row == 0)
                lcd.write(DOWNWARD_SPIKE);
            else
                lcd.write(UPWARD_SPIKE);
            break;
        case LocationType::DEATH:
            lcd.write(SKULL);
            break;
        case LocationType::EMPTY:
            lcd.write(' ');
            break;
        }
    }
}