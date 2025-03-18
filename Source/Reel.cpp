#include "Reel.h"

Reel::Reel(std::initializer_list<int> sprites)
    : sprites_(sprites)
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
    if (rotation_ > sprites_.size())
    {
        rotation_ -= sprites_.size();
    }
}

int Reel::GetSpriteByNumber(int number) const
{
    if (number < 0)
    {
        return GetSpriteByNumber(number + sprites_.size());
    }
    if (number < sprites_.size())
    {
        return sprites_[number];
    }
    return sprites_[number % sprites_.size()];
}

float Reel::GetRotation() const
{
    return rotation_;
}
