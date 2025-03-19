#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UserInterface.h"

UserInterface::UserInterface(std::vector<Reel> *reels)
    : reels_(reels),
      window_(sf::VideoMode(800, 600), "Slot Machine"),
      delta_time_(0.0f),
      sprite_size_(128),
      reels_offset_(200.0f, 200.0f)
{
    font_.loadFromFile("DarkGraffiti-Regular.ttf");

    start_button_.setFont(font_);
    start_button_.setString("Play");
    start_button_.setFillColor(sf::Color::White);
    start_button_.setCharacterSize(100);
    start_button_.setPosition(400, 500);

    textures_.reserve(5);
    sprites_.reserve(5);
    for (int i = 0; i < 4; i++)
    {
        sf::Texture texture;
        if (texture.loadFromFile("Sprites.png", sf::IntRect({0, i * sprite_size_ + 1}, {sprite_size_, sprite_size_})))
        {
            texture.setSmooth(true);
            sf::Texture &curent_texture = textures_.emplace_back(texture);
            sprites_.emplace_back(sf::Sprite(curent_texture));
            std::cout << "Add sprite" << i * sprite_size_ + 1 << std::endl;
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
    const int reel_count = reels_->size();

    for (int i = 0; i < reel_count; i++)
    {
        float rotation = (*reels_)[i].GetRotation();
        for (int j = rotation - 2; j <= rotation + 2; j++)
        {
            const int sprite_type = (*reels_)[i].GetSpriteByNumber(j);
            const sf::Sprite &curent_sprite = sprites_[sprite_type];
            const float x_pos = 1.0f * i * sprite_size_ + reels_offset_.x;
            const float y_pos = rotation * sprite_size_ - j * sprite_size_ + reels_offset_.y;
            window_.draw(curent_sprite, sf::RenderStates().transform.translate({x_pos, y_pos}));
        }
    }
    window_.draw(start_button_);
    window_.display();
    delta_time_ = clock.restart().asSeconds();
    std::cout << "FPS: " << (int)(1 / delta_time_) << std::endl;
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
