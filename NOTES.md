## Notes

### General development

Since Atmel Studio isn't available on Linux and using it through Windows VM is quite painful, I started the development using Arduino IDE. The codebase grew quite quickly and soon became unmanagable. Luckily, I stumbled across [platformio](https://platformio.org/) extension to VSCode. That allowed me to clean up everything and continue development.

### Joystick

It was necessary to use analog-to-digital converter to read values of the displacement of x and y axis.

### Display

Probably the most complex part was to implement communication with the display. I've used datasheet as much as I could but had to read the code of LiquidCrystal library as it was easier than debugging.
