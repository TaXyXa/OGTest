#include <vector>
#include <memory>

#include "StateMachine.h"
#include "UserInterface.h"
#include "Reel.h"

class SlotMachine
{
public:
    SlotMachine();
    void Start();

private:
    std::vector<Reel> reels_;
    StateMachine state_machine_;
    std::unique_ptr<UserInterface> interface_;
};