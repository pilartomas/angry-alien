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
    SPIKE,
    DEATH
};
enum Move
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};

template <size_t HEIGHT, size_t WIDTH>
class Engine
{
public:
    Engine()
    {
        reset();
    }

    void reset()
    {
        status = RUNNING;
        score = 0;
        for (size_t j = 0; j < HEIGHT; ++j)
        {
            for (size_t i = 0; i < WIDTH; ++i)
            {
                state[j][i] = EMPTY;
            }
        }
        state[1][0] = AGENT;
    }

    void action(Move move)
    {
        if (status != RUNNING)
            return;

        auto agent = getAgent();
        switch (move)
        {
        case LEFT:
            if (agent.x > 0)
                moveAgentTo(agent.x - 1, agent.y);
            break;
        case RIGHT:
            if (agent.x < WIDTH - 1)
                moveAgentTo(agent.x + 1, agent.y);
            break;
        case UP:
            if (agent.y > 0)
                moveAgentTo(agent.x, agent.y - 1);
            break;
        case DOWN:
            if (agent.y < HEIGHT - 1)
                moveAgentTo(agent.x, agent.y + 1);
            break;
        }
    }

    void step()
    {
        if (status != RUNNING)
            return;
        score++;
        shiftState();
    }

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

    Agent getAgent() const
    {
        Agent agent;
        for (size_t j = 0; j < HEIGHT; ++j)
        {
            for (size_t i = 0; i < WIDTH; ++i)
            {
                if (state[j][i] == AGENT)
                {
                    agent.x = i;
                    agent.y = j;
                }
            }
        }
        return agent;
    }

    void moveAgentTo(size_t x, size_t y)
    {
        if (state[y][x] == EMPTY)
        {
            auto agent = getAgent();
            state[y][x] = AGENT;
            state[agent.y][agent.x] = EMPTY;
        }
        else if (state[y][x] == SPIKE)
            status = FINISHED;
    }

    void generateStateTail()
    {
        state[0][WIDTH - 1] = EMPTY;
        state[1][WIDTH - 1] = EMPTY;

        auto r = rand();
        auto type = r < RAND_MAX / 3 ? DEATH : SPIKE;
        if (r % SPIKE_AVG_FREQENCY == 0)
        {
            if (r < RAND_MAX / 2 && !isThreat(state[1][WIDTH - 2])) //also make sure it's not a death trap
                state[0][WIDTH - 1] = type;
            else if (!isThreat(state[0][WIDTH - 2]))
                state[1][WIDTH - 1] = type;
        }
    }

    void shiftState()
    {
        auto agent = getAgent();
        moveAgentTo(agent.x + 1, agent.y);
        for (size_t j = 0; j < HEIGHT; ++j)
        {
            for (size_t i = 0; i < WIDTH - 1; ++i)
            {
                state[j][i] = state[j][i + 1];
            }
        }
        generateStateTail();
    }

    static bool isThreat(const LocationType type)
    {
        switch (type)
        {
        case DEATH:
            return true;
        case SPIKE:
            return true;
        default:
            return false;
        }
    }
};