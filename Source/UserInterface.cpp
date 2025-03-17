#include <SFML/Graphics.hpp>
#include <iostream>

#include "UserInterface.h"

UserInterface::UserInterface(std::vector<Reel> *reels)
    : reels_(reels),
      window_(sf::VideoMode(800, 600), "Slot Machine"),
      delta_time_(0.0f)
{
    if (!font_.loadFromFile("ARIAL.TTF"))
    {
        std::cout << "cant find font" << std::endl;
    }

    start_button_.setFont(font_);
    start_button_.setString("Play");
    start_button_.setFillColor(sf::Color::White);
    start_button_.setCharacterSize(30);
    start_button_.setPosition(400, 500);
}

bool UserInterface::IsWindowOpen() const
{
    return window_.isOpen();
}

void UserInterface::Render()
{
    window_.clear();
    window_.draw(start_button_);
    window_.display();
    delta_time_ = clock.restart().asSeconds();
}

void UserInterface::HandleEvents()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }
    }
}

bool UserInterface::IsButtonPressed() const
{
    return sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
           start_button_.getGlobalBounds().contains(sf::Mouse::getPosition(window_).x,
                                                    sf::Mouse::getPosition(window_).y);
}

float UserInterface::GetDeltaTime() const
{
    return delta_time_;
}

void UserInterface::Draw()
{
}
