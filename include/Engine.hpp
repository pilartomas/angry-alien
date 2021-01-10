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

    static const unsigned int WIDTH = 16;
    static const unsigned int HEIGHT = 2;

    LocationType state[HEIGHT][WIDTH];

    Status status;
    unsigned int score;

private:
    void locateAgent(unsigned int &agentX, unsigned int &agentY);

    void moveAgentTo(unsigned int x, unsigned int y);
};