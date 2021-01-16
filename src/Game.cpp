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
        if (joystick.isPressed() && engine.status != Status::RUNNING)
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
    switch (engine.status)
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
    lcd.start(FIRST);
    lcd.print("Score: ");
    lcd.print(itoa(engine.score, buffer, 10));
    lcd.start(SECOND);
    lcd.print("Press to restart");
}

void Game::renderState()
{
    lcd.clear();
    renderRow(FIRST);
    renderRow(SECOND);
}

void Game::renderRow(const Line row)
{
    lcd.start(row);
    for (size_t i = 0; i < WIDTH; ++i)
    {
        switch (engine.state[row == FIRST ? 0 : 1][i])
        {
        case LocationType::AGENT:
            lcd.write(ALIEN);
            break;
        case LocationType::SPIKE:
            if (row == FIRST)
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