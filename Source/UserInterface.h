#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Reel.h"

class Button;

class UserInterface
{
public:
    UserInterface(const std::vector<Reel> *reels);
    bool IsWindowOpen() const;
    // return frame time
    float Update();
    // return once true if Start button or Space was pressed
    bool IsButtonPressed();
    void SetButtonText(const std::string &new_text);
    // resul of roll. Zero will not show
    void SetResult(int result);

private:
    std::unique_ptr<sf::RenderWindow> window_;
    sf::Font font_;
    std::vector<sf::Texture> textures_;
    std::vector<sf::Sprite> sprites_;
    std::unique_ptr<sf::Texture> automat_texture_;
    std::unique_ptr<sf::Sprite> automat_sprite_;
    std::unique_ptr<Button> button_;
    std::unique_ptr<sf::Texture> win_texture_;
    std::unique_ptr<sf::Sprite> win_sprite_;
    std::unique_ptr<sf::Text> win_text_;
    sf::Clock clock;
    const std::vector<Reel> *reels_;
    const sf::Vector2f reels_offset_;
    const int reel_count_;
    const int sprite_size_;
    int result_;
};

class Button : public sf::Drawable
{
public:
    Button(int x_size, int y_size, int x_coordinates, int y_coordinates);
    bool IsButtonPressed(const sf::Window &window);
    void SetText(const std::string &new_text);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool was_pressed_;
    sf::Font font_;
    std::unique_ptr<sf::Text> text_;
    std::unique_ptr<sf::Texture> texture_;
    std::unique_ptr<sf::Sprite> sprite_;
};
