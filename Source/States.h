#pragma once

#include <vector>

#include "Reel.h"

class State
{
public:
    State(std::vector<Reel> &reels);
    // return true if Execute is complite (to change state)
    virtual bool Update(float delta_time) = 0;
    virtual ~State() = default;
    std::vector<Reel> &GetReels() const;

private:
    std::vector<Reel> &reels_;
};

class IdleState : public State
{
public:
    IdleState(std::vector<Reel> &reels);
    bool Update(float delta_time) override;
};

class StartRollState : public State
{
public:
    StartRollState(std::vector<Reel> &reels, float acceleration);
    bool Update(float delta_time) override;

private:
    const float acceleration_;
};

class RollState : public State
{
public:
    RollState(std::vector<Reel> &reels, float timer);
    bool Update(float delta_time) override;

private:
    float curent_timer_;
    const float timer_duration_;
};

class EndRollState : public State
{
public:
    EndRollState(std::vector<Reel> &reels, float acceleration);
    bool Update(float delta_time) override;

private:
    const float acceleration_;
};
