#pragma once

#include <SFML/Graphics.hpp>

#include "Reel.h"

class Button : public sf::Drawable
{
public:
    Button(int x_size, int y_size, int x_coordinates, int y_coordinates);
    Button &operator=(const Button &other_button);
    bool IsButtonPressed(const sf::Window &window);

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
    float GetDeltaTime() const;
    void SetResult(int result);

private:
    sf::RenderWindow window_;
    std::vector<Reel> *reels_;
    std::vector<sf::Texture> textures_;
    std::vector<sf::Sprite> sprites_;
    sf::Vector2f reels_offset_;
    sf::Font font_;
    Button button_;
    sf::Clock clock;
    float delta_time_;
    int sprite_size_;
    int result_;
};
