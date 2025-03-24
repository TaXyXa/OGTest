#include "Reel.h"

Reel::Reel(std::initializer_list<int> symbols_types)
    : symbols_(symbols_types)
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
    if (rotation_ > symbols_.size())
    {
        rotation_ -= symbols_.size();
    }
}

int Reel::GetSpriteByNumber(int number) const
{
    if (number < 0)
    {
        return GetSpriteByNumber(number + symbols_.size());
    }
    if (number < symbols_.size())
    {
        return symbols_[number];
    }
    return symbols_[number % symbols_.size()];
}

float Reel::GetRotation() const
{
    return rotation_;
}

void Reel::SetRotation(float new_rotation)
{
    rotation_ = new_rotation;
}
