#pragma once

#include <vector>

class Reel
{
public:
    Reel(std::initializer_list<int> shapes);
    void SetRotationSpeed(float new_speed);
    float GetRotationSpeed() const;
    float GetMaxRotationSpeed() const;
    void Rotate(float delta_time);
    int GetSpriteByNumber(int number) const;
    float GetRotation() const;

private:
    std::vector<int> sprites_;
    float speed_ = 0.0f;
    float rotation_ = 0.0f;
    const float max_speed_ = 1;
};