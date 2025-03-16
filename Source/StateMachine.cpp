#include <vector>
#include <memory>

#include "States.h"
#include "StateMachine.h"

StateMachine::StateMachine(std::vector<Reel> *reels)
    : reels_(reels), curent_state_(0)
{
    states_.push_back(std::make_shared<IdleState>(*reels_));
    states_.push_back(std::make_shared<StartRollState>(*reels_, 1.0f));
    states_.push_back(std::make_shared<RollState>(*reels_, 3.0f));
    states_.push_back(std::make_shared<EndRollState>(*reels_, 1.0f));
}

void StateMachine::Update(float delta_time)
{
    if (next_state_)
    {
        NextState();
    }
    next_state_ = states_[curent_state_]->Update(delta_time);
}

void StateMachine::Start()
{
    if (curent_state_ == 0)
    {
        NextState();
    }
}

void StateMachine::Stop()
{
    if (curent_state_ == 2)
    {
        NextState();
    }
}

void StateMachine::NextState()
{
    curent_state_++;
    if (curent_state_ == states_.size())
    {
        curent_state_ = 0;
    }
}
