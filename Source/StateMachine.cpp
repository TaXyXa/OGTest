#include <vector>
#include <memory>

#include "States.h"
#include "StateMachine.h"
#include "UserInterface.h"

StateMachine::StateMachine()
    : reels_({Reel({0, 1, 4, 6, 7, 5, 2, 3, 4, 3, 2, 6, 1, 7, 0}),
              Reel({6, 2, 7, 3, 5, 4, 2, 1, 6, 0, 7, 2, 4, 3, 0}),
              Reel({1, 5, 0, 4, 3, 6, 2, 7, 3, 5, 2, 1, 6, 7, 2}),
              Reel({5, 0, 3, 7, 5, 3, 4, 4, 3, 5, 5, 1, 1, 2, 3}),
              Reel({1, 4, 5, 6, 0, 7, 4, 3, 5, 2, 6, 3, 7, 1, 4})}),
      curent_state_(0),
      interface_(std::make_unique<UserInterface>(&reels_))
{
    states_.push_back(std::make_shared<IdleState>(reels_));
    states_.push_back(std::make_shared<StartRollState>(reels_));
    states_.push_back(std::make_shared<RollState>(reels_, 2.0f));
    states_.push_back(std::make_shared<StopRollState>(reels_));
    states_.push_back(std::make_shared<ShowResultState>(reels_, 2.0f));
}

void StateMachine::Start()
{
    float delta_time = 0.0f;
    while (interface_->IsWindowOpen())
    {
        if (interface_->IsButtonPressed())
        {
            ButtonEvent();
        }
        Update(delta_time);
        interface_->Update();
        delta_time = interface_->GetDeltaTime();
    }
}

void StateMachine::Update(float delta_time)
{
    if (next_state_)
    {
        NextState();

        if (curent_state_ == 4)
        {
            int result = dynamic_cast<ShowResultState *>(states_[curent_state_].get())->CalculateResult();
            interface_->SetResult(result);
        }
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
        states_[1]->Fast();
        states_[2]->Fast();
        states_[3]->Fast();
        break;
    case 2:
        states_[2]->Fast();
        states_[3]->Fast();
        break;
    case 3:
        states_[3]->Fast();
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
