#include <vector>
#include <memory>

#include "Reel.h"
#include "SlotMachine.h"
#include "StateMachine.h"
#include "UserInterface.h"

SlotMachine::SlotMachine()
    : reels_({Reel(), Reel(), Reel()}), state_machine_(reels_)
{
    interface_ = std::make_unique<UserInterface>();
}

void SlotMachine::Start()
{
    bool continue_game = true;
    while (continue_game)
    {
        float delta_time = 0.1f;
        state_machine_.Update(delta_time);
        interface_->Draw();
    }
}