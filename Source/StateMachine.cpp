#include <vector>
#include <memory>

#include "States.h"
#include "StateMachine.h"
#include "UserInterface.h"

StateMachine::StateMachine()
    : reels_({Reel({0, 1, 0, 2, 1, 0, 1, 0, 1, 2, 0, 0, 2, 3, 3, 0, 1, 0, 2, 0, 0, 3, 3, 0, 4, 0, 2, 2, 4, 1}),
              Reel({2, 3, 1, 2, 0, 0, 4, 2, 1, 3, 0, 2, 4, 1, 0, 0, 1, 0, 0, 3, 1, 0, 2, 0, 1, 0, 0, 2, 3, 0}),
              Reel({2, 0, 2, 0, 2, 0, 0, 1, 0, 0, 1, 3, 3, 2, 4, 0, 3, 0, 3, 1, 0, 1, 0, 1, 4, 2, 2, 0, 1, 0}),
              Reel({4, 0, 2, 0, 0, 0, 1, 0, 0, 3, 2, 0, 0, 1, 0, 1, 2, 1, 0, 2, 2, 3, 3, 0, 1, 3, 1, 2, 0, 4}),
              Reel({2, 3, 1, 3, 0, 0, 0, 3, 1, 0, 2, 0, 4, 2, 0, 0, 1, 2, 0, 4, 2, 0, 1, 1, 1, 0, 2, 0, 3, 0})}),
      interface_(std::make_unique<UserInterface>(&reels_)),
      curent_state_(0),
      next_state_(false)
{
    states_.push_back(std::make_shared<IdleState>(reels_));
    states_.push_back(std::make_shared<StartRollState>(reels_));
    states_.push_back(std::make_shared<RollState>(reels_));
    states_.push_back(std::make_shared<StopRollState>(reels_));
    states_.push_back(std::make_shared<ShowResultState>(reels_));
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
        delta_time = interface_->Update();
    }
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
        dynamic_cast<ShowResultState *>(states_[4].get())->ResetTimer();
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

    switch (curent_state_)
    {
    case 0:
        interface_->SetResult(0);
        interface_->SetButtonText("START");
        break;
    case 1:
        interface_->SetButtonText("STOP");
        break;
    case 4:
        interface_->SetResult(dynamic_cast<ShowResultState *>(states_[curent_state_].get())->CalculateResult());
        interface_->SetButtonText("START");
        break;
    default:
        break;
    }
}
