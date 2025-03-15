#include <SFML/Graphics.hpp>

class Reel
{
public:
    Reel();
    void SetRotationSpeed();
    void Rotate(float delta_time);
    void Draw(sf::RenderWindow &window) const;
    int GetShapeType() const;

private:
    std::vector<std::unique_ptr<sf::Shape>> shapes_;
    float speed_ = 0.0f;
    float rotation_ = 0.0f;
    static const int max_speed_ = 1;
};