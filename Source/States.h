#include <vector>

#include "Reel.h"

class State
{
public:
    State();
    // return true if Execute is complite (to change state)
    virtual bool Update(float delta_time) = 0;
    virtual ~State() = default;

protected:
    std::vector<Reel> *reels_ = nullptr;
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
    StartRollState(std::vector<Reel> &reels);
    bool Update(float delta_time) override;
};

class RollState : public State
{
public:
    RollState(std::vector<Reel> &reels);
    bool Update(float delta_time) override;
};

class EndRollState : public State
{
public:
    EndRollState(std::vector<Reel> &reels);
    bool Update(float delta_time) override;
};
