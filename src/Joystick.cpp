#include "Joystick.hpp"

#include <avr/io.h>

extern "C" void joystickInitImpl();
extern "C" int analogReadImpl();

#define IDLE_VALUE 512

Joystick::Joystick(unsigned int sensitivity) : invertedSensitivity(IDLE_VALUE - sensitivity)
{
    joystickInitImpl();
}

unsigned int Joystick::getX() const
{
    ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0);
    return analogRead();
}

unsigned int Joystick::getY() const
{
    ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1);
    ADMUX |= (1 << MUX0);
    return analogRead();
}

bool Joystick::isUp() const
{
    auto y = getY();
    if (y < IDLE_VALUE)
        return false;
    return y - IDLE_VALUE > invertedSensitivity;
}

bool Joystick::isDown() const
{
    auto y = getY();
    if (y >= IDLE_VALUE)
        return false;
    return IDLE_VALUE - y > invertedSensitivity;
}

bool Joystick::isLeft() const
{
    auto x = getX();
    if (x > IDLE_VALUE)
        return false;
    return IDLE_VALUE - x > invertedSensitivity;
}

bool Joystick::isRight() const
{
    auto x = getX();
    if (x < IDLE_VALUE)
        return false;
    return x - IDLE_VALUE > invertedSensitivity;
}

bool Joystick::isPressed() const
{
    return (PINB & (1 << PINB0)) == 0;
}

unsigned int Joystick::analogRead() const
{
    return analogReadImpl();
}