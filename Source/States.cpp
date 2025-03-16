#include <vector>

#include "Reel.h"
#include "States.h"

State::State(std::vector<Reel> &reels)
    : reels_(reels)
{
}

std::vector<Reel> &State::GetReels() const
{
    return reels_;
}

IdleState::IdleState(std::vector<Reel> &reels)
    : State(reels)
{
}

bool IdleState::Update(float delta_time)
{
    for (Reel &reel : GetReels())
    {
        reel.SetRotationSpeed(0.0f);
        reel.Rotate(delta_time);
    }
    return false;
}

StartRollState::StartRollState(std::vector<Reel> &reels, float acceleration)
    : State(reels), acceleration_(acceleration)
{
}

bool StartRollState::Update(float delta_time)
{
    bool reels_overclocked = true;
    for (Reel &reel : GetReels())
    {
        reel.SetRotationSpeed(reel.GetRotationSpeed() + delta_time * acceleration_);
        reel.Rotate(delta_time);
        if (reel.GetRotationSpeed() < reel.GetMaxRotationSpeed())
        {
            reels_overclocked = false;
        }
    }
    return reels_overclocked;
}

RollState::RollState(std::vector<Reel> &reels, float timer_duration)
    : State(reels), curent_timer_(timer_duration), timer_duration_(timer_duration)
{
}

bool RollState::Update(float delta_time)
{
    for (Reel &reel : GetReels())
    {
        reel.Rotate(delta_time);
    }
    curent_timer_ -= delta_time;
    if (curent_timer_ <= 0)
    {
        curent_timer_ = timer_duration_;
        return true;
    }
    return false;
}

EndRollState::EndRollState(std::vector<Reel> &reels, float acceleration)
    : State(reels), acceleration_(acceleration)
{
}

bool EndRollState::Update(float delta_time)
{
    bool reels_stoped = true;
    for (Reel &reel : GetReels())
    {
        if (reel.GetRotationSpeed() > 0)
        {
            reel.SetRotationSpeed(reel.GetRotationSpeed() - delta_time * acceleration_);
            reel.Rotate(delta_time);
            reels_stoped = false;
        }
        else
        {
            reel.SetRotationSpeed(0.0f);
        }
    }
    return reels_stoped;
}
