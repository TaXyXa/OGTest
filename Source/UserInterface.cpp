#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

#include "UserInterface.h"

UserInterface::UserInterface(std::vector<Reel> *reels)
    : reels_(reels),
      window_(sf::VideoMode(800, 600), "Slot Machine"),
      delta_time_(0.0f),
      sprite_size_(128)
{
    font_.loadFromFile("ARIAL.TTF");

    start_button_.setFont(font_);
    start_button_.setString("Play");
    start_button_.setFillColor(sf::Color::White);
    start_button_.setCharacterSize(30);
    start_button_.setPosition(400, 500);

    textures_.reserve(5);
    sprites_.reserve(5);
    for (int i = 0; i < 4; i++)
    {
        sf::Texture texture;
        if (texture.loadFromFile("Sprites.png", sf::IntRect({0, i * sprite_size_}, {sprite_size_, sprite_size_})))
        {
            texture.setSmooth(true);
            sf::Texture &curent_texture = textures_.emplace_back(texture);
            sprites_.emplace_back(sf::Sprite(curent_texture));
            std::cout << "Add sprite" << std::endl;
        }
        else
        {
            sprites_.emplace_back(sf::Sprite());
        }
    }
}

bool UserInterface::IsWindowOpen() const
{
    return window_.isOpen();
}

void UserInterface::Render()
{
    window_.clear();
    // curent_sprites_.clear();
    window_.draw(start_button_);
    for (int i = 0; i < reels_->size(); i++)
    {
        float rotate = (*reels_)[i].GetRotation();
        for (int j = rotate - 2; j <= rotate + 2; j++)
        {
            int sprite_type = (*reels_)[i].GetSpriteByNumber(j);
            sf::Sprite curent_sprite = sprites_[sprite_type];
            curent_sprite.setPosition({1.0f * i * sprite_size_ + 20, j * sprite_size_ + (rotate - (int)rotate) * sprite_size_});
            window_.draw(curent_sprite);
        }
    }
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
