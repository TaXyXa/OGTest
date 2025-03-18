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
    states_.push_back(std::make_shared<ShowResultState>(*reels_, 2.0f));
}

void StateMachine::Update(float delta_time)
{
    if (next_state_)
    {
        NextState();
    }
    next_state_ = states_[curent_state_]->Update(delta_time);
}

void StateMachine::ButtonEvent()
{
    switch (curent_state_)
    {
    case 0:
        NextState();
        break;
    case 1:
        // states_[1]->Fast();
        // states_[2]->Fast();
        // states_[3]->Fast();
        break;
    case 2:
        // states_[2]->Fast();
        // states_[3]->Fast();
        break;
    case 3:
        // states_[3]->Fast();
        break;
    case 4:
        NextState();
        NextState();
        break;

    default:
        break;
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
