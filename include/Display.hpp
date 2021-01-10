#include <stdint.h>

/*
 * Controls 16x2 LCD HD44780 driven display with 5x8 pixel characters
 * 
 * RS on pin 0 (PORTD0)
 * E  on pin 1 (PORTD1)
 * D4 on pin 4 (PORTD4)
 * D5 on pin 5 (PORTD5)
 * D6 on pin 6 (PORTD6)
 * D7 on pin 7 (PORTD7)
 */

#define RS (1 << PORTD0)
#define E (1 << PORTD1)

#define CMD_CLEAR 0x01
#define CMD_SETDDRAMADDR 0x80
#define CMD_SETCGRAMADDR 0x40

enum Line
{
    FIRST = 0x00,
    SECOND = 0x40
}; // values are actual DDRAM addresses of the line

enum Image
{
    ALIEN = 0
};

struct Display
{
public:
    Display();

    void write(unsigned char c);

    void write(Image image);

    void print(const char *c);

    void clear();

    void start(Line line);

private:
    const uint8_t Alien[8] = {
        0b11111,
        0b10101,
        0b11111,
        0b11111,
        0b01110,
        0b01010,
        0b11011,
        0b00000};

    void enable();

    void writeNibble(uint8_t nibble);

    void writeCommand(uint8_t command);

    void writeMemory(uint8_t data);
};