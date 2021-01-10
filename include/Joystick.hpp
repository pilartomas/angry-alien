class Joystick
{
public:
    Joystick();

    unsigned int getX() const;

    unsigned int getY() const;

    bool isUp() const;

    bool isDown() const;

    bool isLeft() const;

    bool isRight() const;

    bool isPressed() const;

private:
    const unsigned int IDLE_VALUE = 512;
    const unsigned int TRIGGER_DIFF = 250;

    unsigned int analogRead() const;
};