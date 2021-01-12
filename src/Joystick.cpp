#include "Joystick.hpp"

#include <avr/io.h>

Joystick::Joystick()
{
    DDRB &= ~(1 << DDB0);
    ADMUX |= (1 << REFS0);
    ADCSRA |= (1 << ADEN);
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
    return y - IDLE_VALUE > DIFF_TRESHOLD;
}

bool Joystick::isDown() const
{
    auto y = getY();
    if (y > IDLE_VALUE)
        return false;
    return IDLE_VALUE - y > DIFF_TRESHOLD;
}

bool Joystick::isLeft() const
{
    auto x = getX();
    if (x > IDLE_VALUE)
        return false;
    return IDLE_VALUE - x > DIFF_TRESHOLD;
}

bool Joystick::isRight() const
{
    auto x = getX();
    if (x < IDLE_VALUE)
        return false;
    return x - IDLE_VALUE > DIFF_TRESHOLD;
}

bool Joystick::isPressed() const
{
    return (PINB & (1 << PINB0)) == 0;
}

unsigned int Joystick::analogRead() const
{
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC))
    {
        // wait for the reading
    }
    return ADC;
}