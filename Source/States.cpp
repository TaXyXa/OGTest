#include <vector>

#include "Reel.h"
#include "States.h"

IdleState::IdleState(std::vector<Reel> &reels)
{
}

bool IdleState::Update(float delta_time)
{
}

StartRollState::StartRollState(std::vector<Reel> &reels)
{
}

bool StartRollState::Update(float delta_time)
{
}

RollState::RollState(std::vector<Reel> &reels)
{
}

bool RollState::Update(float delta_time)
{
}

EndRollState::EndRollState(std::vector<Reel> &reels)
{
}

bool EndRollState::Update(float delta_time)
{
}
