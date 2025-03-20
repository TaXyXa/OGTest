#pragma once

#include <vector>
#include <memory>

#include "States.h"
#include "UserInterface.h"
#include "Reel.h"

class StateMachine
{
public:
    StateMachine();
    void Start();
    void Update(float delta_time);
    void ButtonEvent();
    void NextState();

private:
    std::vector<std::shared_ptr<State>> states_;
    std::vector<Reel> reels_;
    std::unique_ptr<UserInterface> interface_;
    int curent_state_;
    bool next_state_ = false;
};