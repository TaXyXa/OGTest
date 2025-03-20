#pragma once

#include <vector>

#include "Reel.h"

class State
{
public:
    State(std::vector<Reel> &reels);
    // return true if State is complite (to change state)
    virtual bool Update(float delta_time) = 0;
    virtual void Fast() = 0;
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
    void Fast() override {};
};

class StartRollState : public State
{
public:
    StartRollState(std::vector<Reel> &reels);
    bool Update(float delta_time) override;
    void Fast() override;

private:
    const float acceleration_;
    bool is_fast;
};

class RollState : public State
{
public:
    RollState(std::vector<Reel> &reels, float timer);
    bool Update(float delta_time) override;
    void Fast() override;

private:
    float curent_timer_;
    const float timer_duration_;
    bool is_fast;
};

class StopRollState : public State
{
public:
    StopRollState(std::vector<Reel> &reels);
    bool Update(float delta_time) override;
    void Fast() override;

private:
    float acceleration_;
    bool is_fast;
};

class ShowResultState : public State
{
public:
    ShowResultState(std::vector<Reel> &reels, float timer);
    bool Update(float delta_time) override;
    void Fast() override {};
    int CalculateResult() const;

private:
    float curent_timer_;
    const float timer_duration_;
};
