#pragma once

#include <SFML/Graphics.hpp>
#include "Reel.h"

class UserInterface
{
public:
    UserInterface(std::vector<Reel> *reels);
    bool IsWindowOpen() const;
    void HandleEvents();
    void Render();
    bool IsButtonPressed() const;
    float GetDeltaTime() const;
    void Draw();

private:
    sf::RenderWindow window_;
    std::vector<Reel> *reels_;
    sf::Font font_;
    sf::Text start_button_;
    sf::Clock clock;
    float delta_time_;
};