#include <stdlib.h>

enum Status
{
    RUNNING,
    PAUSED,
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
    DOWN,
    WAIT
};

struct Engine
{
    Engine();

    void step(Move move);

    void reset();

    void togglePause();

    static const size_t WIDTH = 16;
    static const size_t HEIGHT = 2;

    LocationType state[HEIGHT][WIDTH];

    Status status;
    unsigned int score;

private:
    void locateAgent(size_t &agentX, size_t &agentY);

    void moveAgentTo(size_t x, size_t y);
};