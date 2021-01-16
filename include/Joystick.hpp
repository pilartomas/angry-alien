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
    /*
     * sensitivity - number between 0 and 512 (excluded)
     */
    Joystick(unsigned int sensitivity);

    bool isUp() const;
    bool isDown() const;
    bool isLeft() const;
    bool isRight() const;

    bool isPressed() const;

private:
    const unsigned int invertedSensitivity;

    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int analogRead() const;
};