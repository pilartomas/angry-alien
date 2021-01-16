#include <stdlib.h>

enum class Status
{
    RUNNING,
    FINISHED
};

enum class LocationType
{
    EMPTY,
    AGENT,
    SPIKE,
    DEATH
};

enum class Move
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
        status = Status::RUNNING;
        score = 0;
        for (size_t j = 0; j < HEIGHT; ++j)
        {
            for (size_t i = 0; i < WIDTH; ++i)
            {
                state[j][i] = LocationType::EMPTY;
            }
        }
        state[1][0] = LocationType::AGENT;
    }

    void action(Move move)
    {
        if (status != Status::RUNNING)
            return;

        auto agent = getAgent();
        switch (move)
        {
        case Move::LEFT:
            if (agent.x > 0)
                moveAgentTo(agent.x - 1, agent.y);
            break;
        case Move::RIGHT:
            if (agent.x < WIDTH - 1)
                moveAgentTo(agent.x + 1, agent.y);
            break;
        case Move::UP:
            if (agent.y > 0)
                moveAgentTo(agent.x, agent.y - 1);
            break;
        case Move::DOWN:
            if (agent.y < HEIGHT - 1)
                moveAgentTo(agent.x, agent.y + 1);
            break;
        }
    }

    void step()
    {
        if (status != Status::RUNNING)
            return;
        score++;
        shiftState();
    }

    Status getStatus() const
    {
        return status;
    }

    unsigned int getScore() const
    {
        return score;
    }

    LocationType getState(const size_t y, const size_t x) const
    {
        return state[y][x];
    }

private:
    const unsigned int SPIKE_AVG_FREQENCY = 7;

    Status status;
    unsigned int score;
    LocationType state[HEIGHT][WIDTH];

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
                if (state[j][i] == LocationType::AGENT)
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
        if (state[y][x] == LocationType::EMPTY)
        {
            auto agent = getAgent();
            state[y][x] = LocationType::AGENT;
            state[agent.y][agent.x] = LocationType::EMPTY;
        }
        else if (state[y][x] == LocationType::SPIKE)
            status = Status::FINISHED;
    }

    void generateStateTail()
    {
        state[0][WIDTH - 1] = LocationType::EMPTY;
        state[1][WIDTH - 1] = LocationType::EMPTY;

        auto r = rand();
        auto type = r < RAND_MAX / 3 ? LocationType::DEATH : LocationType::SPIKE;
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
        case LocationType::DEATH:
            return true;
        case LocationType::SPIKE:
            return true;
        default:
            return false;
        }
    }
};