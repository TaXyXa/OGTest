#include <iostream>
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

StartRollState::StartRollState(std::vector<Reel> &reels)
    : State(reels),
      acceleration_(1.0f),
      is_fast(false)
{
}

bool StartRollState::Update(float delta_time)
{
    bool reels_overclocked = true;
    for (Reel &reel : GetReels())
    {
        reel.SetRotationSpeed(reel.GetRotationSpeed() + delta_time * acceleration_ * (is_fast ? 5 : 1));
        reel.Rotate(delta_time);

        if (reel.GetRotationSpeed() < reel.GetMaxRotationSpeed())
        {
            reels_overclocked = false;
        }
    }

    if (!reels_overclocked)
    {
        is_fast = false;
    }
    return reels_overclocked;
}

void StartRollState::Fast()
{
    is_fast = true;
}

RollState::RollState(std::vector<Reel> &reels, float timer_duration)
    : State(reels),
      curent_timer_(timer_duration),
      timer_duration_(timer_duration),
      is_fast(false)
{
}

bool RollState::Update(float delta_time)
{
    for (Reel &reel : GetReels())
    {
        reel.Rotate(delta_time);
    }
    curent_timer_ -= delta_time;
    if (is_fast)
    {
        curent_timer_ = 0;
    }
    if (curent_timer_ <= 0)
    {
        curent_timer_ = timer_duration_;
        is_fast = false;
        return true;
    }
    return false;
}

void RollState::Fast()
{
    is_fast = true;
}

StopRollState::StopRollState(std::vector<Reel> &reels)
    : State(reels),
      is_fast(false),
      acceleration_(1.0f)
{
}

bool StopRollState::Update(float delta_time)
{
    bool reels_stoped = true;
    for (Reel &reel : GetReels())
    {
        if (reel.GetRotationSpeed() > 0)
        {
            reel.SetRotationSpeed(reel.GetRotationSpeed() - delta_time * acceleration_ * (is_fast ? 5 : 1));
            reel.Rotate(delta_time);
            reels_stoped = false;
        }
        else
        {
            reel.SetRotationSpeed(0.0f);
            is_fast = false;
        }
    }
    return reels_stoped;
}

void StopRollState::Fast()
{
    is_fast = true;
}

ShowResultState::ShowResultState(std::vector<Reel> &reels, float timer)
    : State(reels),
      curent_timer_(timer),
      timer_duration_(timer)
{
}

bool ShowResultState::Update(float delta_time)
{
    bool end_show = true;
    if (curent_timer_ > 0)
    {
        curent_timer_ -= delta_time;
        end_show = false;
    }
    else
    {
        curent_timer_ = timer_duration_;
    }
    return end_show;
}

int ShowResultState::CalculateResult() const
{
    return 1;
}