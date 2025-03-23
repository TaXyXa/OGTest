#include <iostream>
#include <vector>
#include <cmath>
#include <random>

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
      acceleration_(5.0f),
      is_fast(false)
{
}

bool StartRollState::Update(float delta_time)
{
    bool reels_overclocked = true;
    for (Reel &reel : GetReels())
    {
        if (reel.GetRotationSpeed() < reel.GetMaxRotationSpeed())
        {
            reels_overclocked = false;
            reel.SetRotationSpeed(reel.GetRotationSpeed() + delta_time * acceleration_ * (is_fast ? 10 : 1));
            reel.Rotate(delta_time);
        }
    }

    if (!reels_overclocked)
    {
        is_fast = false;
    }
    return reels_overclocked;
}

RollState::RollState(std::vector<Reel> &reels)
    : State(reels),
      curent_timer_(2.0f),
      timer_duration_(2.0f),
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

StopRollState::StopRollState(std::vector<Reel> &reels)
    : State(reels),
      is_fast(false),
      accelerations_(reels.size())
{
    RandomAccelerations();
}

bool StopRollState::Update(float delta_time)
{
    bool reels_stoped = true;
    for (int i = 0; i < GetReels().size(); i++)
    {
        Reel &reel = GetReels()[i];
        float curent_speed = reel.GetRotationSpeed();

        if (curent_speed > 0.40f)
        {
            reel.SetRotationSpeed(std::max(0.40f, curent_speed - delta_time * (is_fast ? 2 : 1) * accelerations_[i]));
            reel.Rotate(delta_time);
            reels_stoped = false;
        }
        else
        {
            float curent_rotation = reel.GetRotation();
            if ((curent_rotation - (int)curent_rotation) > 0.2f)
            {
                reel.Rotate(delta_time);
                reels_stoped = false;
            }
            else
            {
                reel.SetRotation((int)curent_rotation);
                reel.SetRotationSpeed(0.0f);
                is_fast = false;
            }
        }
    }
    if (reels_stoped)
    {
        RandomAccelerations();
    }
    return reels_stoped;
}

ShowResultState::ShowResultState(std::vector<Reel> &reels)
    : State(reels),
      value_table_({2, 2, 2, 5, 10}),
      curent_timer_(3.0f),
      timer_duration_(3.0f)
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

void StartRollState::Fast()
{
    is_fast = true;
}

void RollState::Fast()
{
    is_fast = true;
}

void StopRollState::Fast()
{
    is_fast = true;
}

void StopRollState::RandomAccelerations()
{
    for (float &acceleration : accelerations_)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(20, 60);

        acceleration = distrib(gen) / 10.0f;
    }
}

int ShowResultState::CalculateResult() const
{
    int result = 1;
    int unique_count = 0;
    int unique_symbol = -1;
    for (Reel &reel : GetReels())
    {
        int curent_symbol = reel.GetSpriteByNumber(reel.GetRotation());
        if (unique_symbol == curent_symbol)
        {
            unique_count++;
        }
        else if (unique_count < 3)
        {
            unique_symbol = curent_symbol;
            unique_count = 1;
        }
    }
    if (unique_count >= 3)
    {
        for (int i = 1; i <= unique_count; i++)
        {
            result *= value_table_[unique_symbol];
        }
    }
    else
    {
        result = 0;
    }
    return result;
}

void ShowResultState::ResetTimer()
{
    curent_timer_ = timer_duration_;
}
