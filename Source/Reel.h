#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

class Reel
{
public:
    Reel(std::initializer_list<int> shapes);
    void SetRotationSpeed(float new_speed);
    float GetRotationSpeed() const;
    float GetMaxRotationSpeed() const;
    void Rotate(float delta_time);
    void Draw(sf::RenderWindow &window) const;
    int GetShapeType() const;

private:
    std::vector<int> shapes_;
    float speed_ = 0.0f;
    float rotation_ = 0.0f;
    const float max_speed_ = 1;
};