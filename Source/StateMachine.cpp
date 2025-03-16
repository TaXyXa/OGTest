#include <vector>
#include <memory>

#include "States.h"
#include "StateMachine.h"

StateMachine::StateMachine(std::vector<Reel> &reels)
    : reels_(&reels), curent_state_(0)
{
    states_.push_back(std::make_shared<IdleState>(reels_));
    states_.push_back(std::make_shared<StartRollState>(reels_, 0.1f));
    states_.push_back(std::make_shared<RollState>(reels_, 3.0f));
    states_.push_back(std::make_shared<EndRollState>(reels_, 0.1f));
}

void StateMachine::Update(float delta_time)
{
    states_[curent_state_]->Update(delta_time);
}

void StateMachine::NextState()
{
    curent_state_++;
    if (curent_state_ == states_.size())
    {
        curent_state_ = 0;
    }
}
