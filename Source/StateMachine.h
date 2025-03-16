#include <vector>
#include <memory>

#include "States.h"

class StateMachine
{
public:
    StateMachine(std::vector<Reel> &reels);
    void Update(float delta_time);
    void NextState();

private:
    std::vector<std::shared_ptr<State>> states_;
    std::vector<Reel> *reels_;
    int curent_state_;
};