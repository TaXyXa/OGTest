#pragma once

#include <vector>
#include <memory>

#include "States.h"

class StateMachine
{
public:
    StateMachine(std::vector<Reel> *reels);
    void Update(float delta_time);
    void ButtonEvent();
    void NextState();

private:
    std::vector<std::shared_ptr<State>> states_;
    std::vector<Reel> *reels_;
    int curent_state_;
    bool next_state_ = false;
};