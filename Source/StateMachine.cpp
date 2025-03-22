#include <vector>
#include <memory>

#include "States.h"
#include "StateMachine.h"
#include "UserInterface.h"

StateMachine::StateMachine()
    : reels_({Reel({3, 3, 0, 0, 3, 0, 0, 2, 0, 2, 1, 4, 5, 6, 2, 1, 2, 6, 1, 3, 5, 0, 4, 2, 3, 2, 1, 3, 1, 1}),
              Reel({6, 0, 3, 0, 0, 3, 3, 3, 4, 3, 2, 0, 1, 4, 0, 2, 1, 6, 2, 5, 2, 1, 1, 1, 0, 2, 5, 2, 3, 1}),
              Reel({0, 1, 3, 5, 6, 3, 0, 2, 1, 2, 4, 0, 2, 0, 1, 0, 3, 3, 2, 1, 1, 2, 0, 1, 6, 4, 2, 5, 3, 3}),
              Reel({5, 0, 1, 6, 4, 2, 1, 6, 1, 0, 2, 2, 2, 0, 1, 1, 1, 0, 4, 3, 3, 2, 3, 0, 5, 3, 3, 3, 0, 2}),
              Reel({5, 2, 1, 1, 2, 3, 2, 3, 3, 6, 4, 0, 1, 0, 2, 0, 5, 0, 6, 0, 2, 3, 3, 0, 1, 1, 4, 3, 1, 2})}),
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
    switch (curent_state_)
    {
    case 0:
        interface_->SetButtonText("Start");
        break;
    case 1:
        interface_->SetButtonText("Stop");
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        interface_->SetResult(dynamic_cast<ShowResultState *>(states_[curent_state_].get())->CalculateResult());
        interface_->SetButtonText("Start");
        break;

    default:
        break;
    }
}
