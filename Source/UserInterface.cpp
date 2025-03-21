#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UserInterface.h"

UserInterface::UserInterface(std::vector<Reel> *reels)
    : reels_(reels),
      window_(sf::VideoMode(800, 600), "Slot Machine", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize),
      delta_time_(0.0f),
      sprite_size_(128),
      reels_offset_(100.0f, 200.0f),
      button_(128, 64, 400, 500),
      reel_count_(reels_->size())

{
    font_.loadFromFile("DarkGraffiti-Regular.ttf");

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

void UserInterface::Update()
{
    sf::Event event;
    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_.close();
        }
    }
    delta_time_ = clock.restart().asSeconds();

    window_.clear();
    float rotation;
    for (int i = 0; i < reel_count_; i++)
    {
        rotation = (*reels_)[i].GetRotation();
        for (int j = rotation - 2; j <= rotation + 2; j++)
        {
            const int sprite_type = (*reels_)[i].GetSpriteByNumber(j);
            const sf::Sprite &curent_sprite = sprites_[sprite_type];
            const float x_pos = 1.0f * i * sprite_size_ + reels_offset_.x;
            const float y_pos = rotation * sprite_size_ - j * sprite_size_ + reels_offset_.y;
            window_.draw(curent_sprite, sf::RenderStates().transform.translate({x_pos, y_pos}));
        }
    }
    window_.draw(button_);
    window_.display();

    // std::cout << "FPS: " << (int)(1 / delta_time_) << std::endl;
}

bool UserInterface::IsButtonPressed()
{
    return button_.IsButtonPressed(window_);
}

float UserInterface::GetDeltaTime() const
{
    return delta_time_;
}

void UserInterface::SetResult(int result)
{
    result_ = result;
}

Button::Button(int x_size, int y_size, int x_coordinates, int y_coordinates)
    : was_pressed_(false)
{
    font_.loadFromFile("DarkGraffiti-Regular.ttf");
    if (texture_.loadFromFile("Button.png", sf::IntRect({0, 0}, {x_size, y_size})))
    {
        texture_.setSmooth(true);
        sprite_ = sf::Sprite(texture_);
        std::cout << "Add button" << std::endl;
    }
    text_.setString("Start");
    text_.setFont(font_);
    text_.setPosition(x_coordinates, y_coordinates);
    text_.setFillColor(sf::Color::White);
    text_.setCharacterSize(100);
    sprite_.setPosition(x_coordinates, y_coordinates);
}

bool Button::IsButtonPressed(const sf::Window &window)
{
    bool now_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                           sprite_.getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
                                                              sf::Mouse::getPosition(window).y) ||
                       sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space);
    if (now_pressed)
    {
        if (!was_pressed_)
        {
            was_pressed_ = true;
            return was_pressed_;
        }
    }
    else
    {
        if (was_pressed_)
        {
            was_pressed_ = false;
        }
    }
    return false;
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(sprite_, states);
    target.draw(text_, states);
}

Button &Button::operator=(const Button &other_button)
{
    was_pressed_ = false;
    sprite_ = other_button.sprite_;
    texture_ = other_button.texture_;
    text_ = other_button.text_;
    font_ = other_button.font_;
    return *this;
}
