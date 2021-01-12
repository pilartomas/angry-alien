#include "Display.hpp"

#include <avr/io.h>
#include <util/delay.h>

Display::Display()
{
    DDRD |= 0b11110011; // set pins to output

    // init sequence
    PORTD &= ~RS;
    _delay_ms(50);
    writeNibble(0b0011);
    _delay_us(4500);
    writeNibble(0b0011);
    _delay_us(4500);
    writeNibble(0b0011);
    _delay_us(150);
    writeNibble(0b0010);
    writeCommand(0b00101000);
    writeCommand(0b00001111);
    writeCommand(0b00000001);
    writeCommand(0b00000110);

    // init images
    //    byte loc = 0;
    //    loc &= 0x7;
    //    writeCommand(CMD_SETCGRAMADDR);
    //    for (unsigned int i = 0; i < 8; ++i) {
    //      write(Alien[i]);
    //    }

    start(FIRST);
}

void Display::write(unsigned char c)
{
    writeMemory(c);
}

void Display::write(Image image)
{
    writeMemory(image);
}

void Display::print(const char *c)
{
    while (*c != '\0')
    {
        write(*c);
        c++;
    }
}

void Display::clear()
{
    writeCommand(CMD_CLEAR);
    _delay_ms(5); // command needs extra time
}

void Display::start(Line line)
{
    writeCommand(CMD_SETDDRAMADDR | line);
    _delay_ms(5); // command needs extra time
}

void Display::enable()
{
    PORTD &= ~E;
    _delay_us(1);
    PORTD |= E;
    _delay_us(1);
    PORTD &= ~E;
    _delay_us(100);
}

void Display::writeNibble(uint8_t nibble)
{
    PORTD &= 0b00001111;
    PORTD |= nibble << 4;
    enable();
}

void Display::writeCommand(uint8_t command)
{
    PORTD &= ~RS;
    writeNibble(command >> 4);
    writeNibble(command);
}

void Display::writeMemory(uint8_t data)
{
    PORTD |= RS;
    writeNibble(data >> 4);
    writeNibble(data);
}