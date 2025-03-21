#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Reel.h"

class Button : public sf::Drawable
{
public:
    Button(int x_size, int y_size, int x_coordinates, int y_coordinates);
    bool IsButtonPressed(const sf::Window &window);
    void SetText(const std::string &new_text);

private:
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    bool was_pressed_;
    sf::Sprite sprite_;
    sf::Texture texture_;
    sf::Text text_;
    sf::Font font_;
};

class UserInterface
{
public:
    UserInterface(std::vector<Reel> *reels);
    bool IsWindowOpen() const;
    void Update();
    bool IsButtonPressed();
    void SetButtonText(const std::string &new_text);
    float GetDeltaTime() const;
    void SetResult(int result);

private:
    sf::RenderWindow window_;
    sf::Font font_;
    std::vector<sf::Texture> textures_;
    std::vector<sf::Sprite> sprites_;
    std::unique_ptr<sf::Texture> automat_texture_;
    std::unique_ptr<sf::Sprite> automat_sprite_;
    std::unique_ptr<Button> button_;
    std::vector<Reel> *reels_;
    sf::Vector2f reels_offset_;
    sf::Clock clock;
    const int reel_count_;
    float delta_time_;
    int sprite_size_;
    int result_;
};
