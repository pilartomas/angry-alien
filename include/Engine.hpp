#include <stdlib.h>

enum Status
{
    RUNNING,
    FINISHED
};
enum LocationType
{
    EMPTY,
    AGENT,
    SPIKE
};
enum Move
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

struct Engine
{
    Engine();

    void action(Move move);
    void step();
    void reset();

    static const size_t WIDTH = 16;
    static const size_t HEIGHT = 2;

    LocationType state[HEIGHT][WIDTH];

    Status status;
    unsigned int score;

private:
    const unsigned int SPIKE_AVG_FREQENCY = 7;

    struct Agent
    {
        size_t x;
        size_t y;
    };

    Agent getAgent() const;
    void moveAgentTo(size_t x, size_t y);
    void generateStateTail();
    void shiftState();
};