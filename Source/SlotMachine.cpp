#include <vector>
#include <memory>

#include "Reel.h"
#include "SlotMachine.h"
#include "StateMachine.h"
#include "UserInterface.h"

SlotMachine::SlotMachine()
    : reels_({Reel(), Reel(), Reel()}),
      state_machine_(&reels_),
      interface_(std::make_unique<UserInterface>())
{
}

void SlotMachine::Start()
{
    bool continue_game = true;
    while (continue_game)
    {
        if (!interface_->IsWindowOpen())
        {
            continue_game = false;
        }
        if (interface_->IsStartButtonPressed())
        {
            state_machine_.Start();
        }
        if (interface_->IsStopButtonPressed())
        {
            state_machine_.Stop();
        }
        interface_->HandleEvents();

        float delta_time = interface_->GetDeltaTime();
        state_machine_.Update(delta_time);

        interface_->Render();
    }
}