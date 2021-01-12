#include "Engine.hpp"

#include <stdlib.h>

Engine::Engine()
{
    reset();
}

void Engine::step(Move move)
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
    case WAIT:
        break;
    }
    score++;

    shiftState();
}

void Engine::shiftState()
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

    //generate new tail
    generateStateTail();
}

void Engine::reset()
{
    status = PAUSED;
    score = 0;
    for (size_t j = 0; j < HEIGHT; ++j)
    {
        for (size_t i = 0; i < WIDTH; ++i)
        {
            state[j][i] = EMPTY;
        }
    }
    state[1][3] = AGENT;
}

void Engine::toggleStatus()
{
    switch (status)
    {
    case PAUSED:
        status = RUNNING;
        break;
    case RUNNING:
        status = PAUSED;
        break;
    case FINISHED:
        reset();
        break;
    }
}

Engine::Agent Engine::getAgent() const
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

void Engine::moveAgentTo(unsigned int x, unsigned int y)
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

void Engine::generateStateTail()
{
    state[0][WIDTH - 1] = EMPTY;
    state[1][WIDTH - 1] = EMPTY;

    auto r = rand();
    if (r % SPIKE_AVG_FREQENCY == 0)
    {
        if (r < RAND_MAX / 2 && state[1][WIDTH - 2] != SPIKE) //also make sure it's not a death trap
            state[0][WIDTH - 1] = SPIKE;
        else if (state[0][WIDTH - 2] != SPIKE)
            state[1][WIDTH - 1] = SPIKE;
    }
}