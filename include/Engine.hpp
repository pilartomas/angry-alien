#include <stdlib.h>

#define MAX_THREAT_LIKELIHOOD RAND_MAX

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
    DEATH,
    PROJECTILE,
    EXPLOSION
};

enum class Action
{
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    SHOOT
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
        state[HEIGHT / 2][0] = LocationType::AGENT;
    }

    void execute(Action action)
    {
        if (status != Status::RUNNING)
            return;

        auto agent = getAgent();
        switch (action)
        {
        case Action::SHOOT:
            moveProjectileTo(agent.x + 1, agent.y);
            break;
        case Action::MOVE_LEFT:
            moveAgentTo(agent.x - 1, agent.y);
            break;
        case Action::MOVE_RIGHT:
            moveAgentTo(agent.x + 1, agent.y);
            break;
        case Action::MOVE_UP:
            moveAgentTo(agent.x, agent.y - 1);
            break;
        case Action::MOVE_DOWN:
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

    unsigned int threatFrequency = MAX_THREAT_LIKELIHOOD / 2;

private:
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

    void moveProjectileTo(size_t fromX, size_t fromY, size_t toX, size_t toY)
    {
        moveProjectileTo(toX, toY);
        state[fromY][fromX] = LocationType::EMPTY;
    }

    void moveProjectileTo(size_t toX, size_t toY)
    {
        if (toX >= WIDTH || toY >= HEIGHT) // Can't move out of bounds
            return;

        switch (state[toY][toX])
        {
        case LocationType::EMPTY:
            state[toY][toX] = LocationType::PROJECTILE; // flying projectile
            break;
        case LocationType::PROJECTILE:
            state[toY][toX] = LocationType::PROJECTILE; // for simplicity
            break;
        case LocationType::DEATH:
            state[toY][toX] = LocationType::EXPLOSION; // death is killed by the projectile
            score++;
            break;
        case LocationType::EXPLOSION:
            break; // explosion destroys projectile
        case LocationType::AGENT:
            status = Status::FINISHED; // agent shoot itself
            break;
        case LocationType::SPIKE:
            break; // spike blocks projectile
        }
    }

    void moveAgentTo(size_t x, size_t y)
    {
        if (x >= WIDTH || y >= HEIGHT) // Can't move out of bounds
            return;

        if (state[y][x] == LocationType::EMPTY) // Safe move
        {
            auto agent = getAgent();
            state[y][x] = LocationType::AGENT;
            state[agent.y][agent.x] = LocationType::EMPTY;
        }
        else if (isThreat(state[y][x])) // Unsafe move
            status = Status::FINISHED;
    }

    bool canGenerateThreat()
    {
        for (size_t j = 0; j < HEIGHT; ++j)
        {
            auto location = state[j][WIDTH - 2];
            if (isThreat(location))
                return false;
        }
        return true;
    }

    void tryGenerateThreat()
    {
        if (!canGenerateThreat())
            return;

        auto shouldGenerateThreat = (unsigned int)rand() < threatFrequency;
        if (!shouldGenerateThreat)
            return;

        auto threatType = rand() % 3 == 0 ? LocationType::DEATH : LocationType::SPIKE;
        state[rand() % HEIGHT][WIDTH - 1] = threatType;
    }

    void shiftProjectiles()
    {
        for (size_t y = 0; y < HEIGHT; ++y)
        {
            // Right-to-left swipe is needed for this axis
            for (size_t x = WIDTH - 1; x > 0; --x)
            {
                if (state[y][x - 1] == LocationType::PROJECTILE)
                    moveProjectileTo(x - 1, y, x, y);
            }
        }
    }

    void shiftAgent()
    {
        auto agent = getAgent();
        moveAgentTo(agent.x + 1, agent.y);
    }

    void clearExplosions()
    {
        for (size_t y = 0; y < HEIGHT; ++y)
        {
            for (size_t x = 0; x < WIDTH; ++x)
            {
                if (state[y][x] == LocationType::EXPLOSION)
                    state[y][x] = LocationType::EMPTY;
            }
        }
    }

    void shiftState()
    {
        clearExplosions();

        shiftProjectiles();
        shiftAgent();
        shiftProjectiles();

        for (size_t j = 0; j < HEIGHT; ++j)
        {
            for (size_t i = 0; i < WIDTH - 1; ++i)
            {
                state[j][i] = state[j][i + 1];
            }
        }
        state[0][WIDTH - 1] = LocationType::EMPTY;
        state[1][WIDTH - 1] = LocationType::EMPTY;

        tryGenerateThreat();
    }

    static bool isThreat(LocationType type)
    {
        switch (type)
        {
        case LocationType::DEATH:
            return true;
        case LocationType::SPIKE:
            return true;
        case LocationType::PROJECTILE:
            return true;
        default:
            return false;
        }
    }
};