#include <vector>
#include <memory>

#include "Reel.h"
#include "SlotMachine.h"
#include "StateMachine.h"
#include "UserInterface.h"

SlotMachine::SlotMachine()
    : reels_({Reel({0, 1, 2, 3}), Reel({2, 3, 1, 0}), Reel({1, 0, 3, 2})}),
      state_machine_(&reels_),
      interface_(std::make_unique<UserInterface>(&reels_))
{
}

void SlotMachine::Start()
{
    bool continue_game = true;
    bool button_pressed = false;
    while (continue_game)
    {
        if (!interface_->IsWindowOpen())
        {
            continue_game = false;
        }
        if (interface_->IsButtonPressed())
        {
            // problem whit long press
            state_machine_.ButtonEvent();
        }
        interface_->HandleEvents();

        float delta_time = interface_->GetDeltaTime();
        state_machine_.Update(delta_time);

        interface_->Render();
    }
}