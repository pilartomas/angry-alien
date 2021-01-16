#include <stdint.h>

#define DISPLAY_HEIGHT 2
#define DISPLAY_WIDTH 16

enum Image
{
    ALIEN = 0,
    DOWNWARD_SPIKE = 1,
    UPWARD_SPIKE = 2,
    SKULL = 3
};

/*
 * Controls 16x2 LCD HD44780 driven display with 5x8 pixel characters
 * 
 * Dimensions are available as DISPLAY_HEIGHT and DISPLAY_WIDTH definitions 
 * 
 * Connectors
 * RS on pin 0 (PORTD0)
 * E  on pin 1 (PORTD1)
 * D4 on pin 4 (PORTD4)
 * D5 on pin 5 (PORTD5)
 * D6 on pin 6 (PORTD6)
 * D7 on pin 7 (PORTD7)
 */
class Display
{
public:
    Display();
    void write(unsigned char c);
    void write(Image image);
    void print(const char *c);
    void clear();
    void start(unsigned int line);

private:
    void loadImages();
    void loadImage(const Image image, const uint8_t imageData[]);
    void enable();
    void writeNibble(uint8_t nibble);
    void writeCommand(uint8_t command);
    void writeMemory(uint8_t data);
};