/*
 * Controls joystick with horizontal X axis, vertical Y axis and a button
 * 
 * X on pin A0
 * Y on pin A1
 * D on pin 8
 */
class Joystick
{
public:
    Joystick();

    bool isUp() const;
    bool isDown() const;
    bool isLeft() const;
    bool isRight() const;

    bool isPressed() const;

private:
    const unsigned int IDLE_VALUE = 512;
    const unsigned int DIFF_TRESHOLD = 250;

    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int analogRead() const;
};