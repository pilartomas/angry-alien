#include "Display.hpp"

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define RS (1 << PORTD0)
#define E (1 << PORTD1)

#define CMD_CLEAR 0x01
#define CMD_SETDDRAMADDR 0x80
#define CMD_SETCGRAMADDR 0x40

const uint8_t Alien[8] = {
    0b11111,
    0b10101,
    0b11111,
    0b11111,
    0b01110,
    0b01010,
    0b11011,
    0b00000};

const uint8_t Spike[8] = {
    0b00000,
    0b00100,
    0b01110,
    0b01110,
    0b11111,
    0b11111,
    0b11111,
    0b11111};

const uint8_t ReverseSpike[8] = {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b01110,
    0b01110,
    0b00100,
    0b00000};

const uint8_t Skull[8] = {
    0b00000,
    0b01110,
    0b10101,
    0b11011,
    0b01110,
    0b01110,
    0b00000,
    0b00000};

const uint8_t Bullet[8] = {
    0b00000,
    0b00000,
    0b11100,
    0b11111,
    0b11111,
    0b11100,
    0b00000,
    0b00000};

const uint8_t Explosion[8] = {
    0b00000,
    0b10001,
    0b00100,
    0b01110,
    0b00100,
    0b10001,
    0b00000,
    0b00000};

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
    _delay_us(4500);
    loadImages();

    start(0);
}

void Display::loadImages()
{
    loadImage(ALIEN, Alien);
    loadImage(DOWNWARD_SPIKE, ReverseSpike);
    loadImage(UPWARD_SPIKE, Spike);
    loadImage(SKULL, Skull);
    loadImage(BULLET, Bullet);
    loadImage(EXPLOSION, Explosion);
}

void Display::loadImage(const Image image, const uint8_t imageData[])
{
    uint8_t location = image;
    location &= 0x7;
    writeCommand(CMD_SETCGRAMADDR | (location << 3));
    for (size_t i = 0; i < 8; ++i)
    {
        writeMemory(imageData[i]);
        _delay_us(4500);
    }
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

enum Line
{
    FIRST = 0x00,
    SECOND = 0x40
}; // values are actual DDRAM addresses of the line

void Display::start(unsigned int line)
{
    switch (line)
    {
    case 0:
        writeCommand(CMD_SETDDRAMADDR | Line::FIRST);
        break;
    case 1:
        writeCommand(CMD_SETDDRAMADDR | Line::SECOND);
        break;
    }
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