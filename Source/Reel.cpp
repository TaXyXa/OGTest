#include <SFML/Graphics.hpp>

#include "Reel.h"

Reel::Reel()
{
}

void Reel::SetRotationSpeed(float new_speed)
{
    speed_ = new_speed;
}

float Reel::GetRotationSpeed() const
{
    return speed_;
}

float Reel::GetMaxRotationSpeed() const
{
    return max_speed_;
}

void Reel::Rotate(float delta_time)
{
    rotation_ += speed_ * delta_time;
    if (rotation_ > shapes_.size())
    {
        rotation_ -= shapes_.size();
    }
}

void Reel::Draw(sf::RenderWindow &window) const
{
}

int Reel::GetShapeType() const
{
    return (int)rotation_;
}