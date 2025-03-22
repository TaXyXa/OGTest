#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "UserInterface.h"

UserInterface::UserInterface(std::vector<Reel> *reels)
    : window_(sf::VideoMode(800, 600), "Slot Machine", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize),
      button_(std::make_unique<Button>(120, 60, 600, 520)),
      reels_(reels),
      reels_offset_(80.0f, 206.0f),
      reel_count_(reels->size()),
      delta_time_(0.0f),
      sprite_size_(128)
{
    window_.setFramerateLimit(60);
    font_.loadFromFile("DarkGraffiti-Regular.ttf");

    int number_of_symbols = 8;
    textures_.reserve(number_of_symbols);
    sprites_.reserve(number_of_symbols);
    sf::Texture texture;
    for (int i = 0; i < number_of_symbols; i++)
    {
        if (texture.loadFromFile("Sprites.png", sf::IntRect({0, i * sprite_size_}, {sprite_size_, sprite_size_})))
        {
            texture.setSmooth(true);
            sf::Texture &curent_texture = textures_.emplace_back(texture);
            sprites_.emplace_back(sf::Sprite(curent_texture));
        }
        else
        {
            sprites_.emplace_back(sf::Sprite());
        }
    }

    if (texture.loadFromFile("Automat.png", sf::IntRect({0, 0}, {800, 600})))
    {
        automat_texture_ = std::make_unique<sf::Texture>(texture);
        automat_texture_->setSmooth(true);
        automat_sprite_ = std::make_unique<sf::Sprite>(*automat_texture_);
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
            const float x_pos = i * sprite_size_ + reels_offset_.x;
            const float y_pos = rotation * sprite_size_ - j * sprite_size_ + reels_offset_.y;
            window_.draw(curent_sprite, sf::RenderStates().transform.translate({x_pos, y_pos}));
        }
    }
    window_.draw(*automat_sprite_);
    window_.draw(*button_);
    window_.display();
}

bool UserInterface::IsButtonPressed()
{
    return button_->IsButtonPressed(window_);
}

void UserInterface::SetButtonText(const std::string &new_text)
{
    button_->SetText(new_text);
}

float UserInterface::GetDeltaTime() const
{
    return delta_time_;
}

void UserInterface::SetResult(int result)
{
    result_ = result;
    std::cout << result << std::endl;
}

Button::Button(int x_size, int y_size, int x_coordinates, int y_coordinates)
    : was_pressed_(false)
{
    font_.loadFromFile("DarkGraffiti-Regular.ttf");
    if (texture_.loadFromFile("Button.png", sf::IntRect({0, 0}, {x_size, y_size})))
    {
        texture_.setSmooth(true);
        sprite_ = sf::Sprite(texture_);
    }
    text_.setString("Start");
    text_.setFont(font_);
    text_.setPosition(x_coordinates + 5, y_coordinates - 5);
    text_.setFillColor(sf::Color::Black);
    text_.setCharacterSize(64);
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

void Button::SetText(const std::string &new_text)
{
    text_.setString(new_text);
}
