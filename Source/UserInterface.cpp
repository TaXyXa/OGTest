#include "UserInterface.h"

UserInterface::UserInterface(const std::vector<Reel> *reels)
    : window_(std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "Slot Machine", sf::Style::Close | sf::Style::Titlebar)),
      button_(std::make_unique<Button>(200, 70, 400, 545)),
      reels_(reels),
      reels_offset_(80.0f, 206.0f),
      reel_count_(reels->size()),
      sprite_size_(128),
      result_(0)
{
    font_.loadFromFile("Source/DarkGraffiti-Regular.ttf");

    int number_of_symbols = 5;
    textures_.reserve(number_of_symbols);
    sprites_.reserve(number_of_symbols);
    sf::Texture texture;
    for (int i = 0; i < number_of_symbols; i++)
    {
        if (texture.loadFromFile("Source/Symbols.png", sf::IntRect({0, i * sprite_size_}, {sprite_size_, sprite_size_})))
        {
            texture.setSmooth(true);
            sf::Texture &curent_texture = textures_.emplace_back(texture);
            sprites_.emplace_back(sf::Sprite(curent_texture));
        }
    }

    automat_texture_ = std::make_unique<sf::Texture>();
    if (automat_texture_->loadFromFile("Source/Automat.png", sf::IntRect({0, 0}, {800, 600})))
    {
        automat_texture_->setSmooth(true);
        automat_sprite_ = std::make_unique<sf::Sprite>(*automat_texture_);
    }

    win_texture_ = std::make_unique<sf::Texture>();
    if (win_texture_->loadFromFile("Source/Win.png", sf::IntRect({0, 0}, {640, 382})))
    {
        win_texture_->setSmooth(true);
        win_sprite_ = std::make_unique<sf::Sprite>(*win_texture_);
        sf::FloatRect win_bounds = win_sprite_->getLocalBounds();
        win_sprite_->setOrigin(win_bounds.width / 2, win_bounds.height / 2);
        win_sprite_->setPosition({400, 270});
    }

    win_text_ = std::make_unique<sf::Text>();
    win_text_->setFont(font_);
    win_text_->setFillColor(sf::Color::Black);
    win_text_->setCharacterSize(128);
    win_text_->setPosition({400, 340});
}

bool UserInterface::IsWindowOpen() const
{
    return window_->isOpen();
}

float UserInterface::Update()
{
    sf::Event event;
    while (window_->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window_->close();
        }
    }

    window_->clear();

    for (int i = 0; i < reel_count_; i++)
    {
        float rotation = (*reels_)[i].GetRotation();
        for (int j = rotation - 2; j <= rotation + 2; j++)
        {
            const int sprite_type = (*reels_)[i].GetSpriteByNumber(j);
            const sf::Sprite &curent_sprite = sprites_[sprite_type];
            const float x_pos = i * sprite_size_ + reels_offset_.x;
            const float y_pos = rotation * sprite_size_ - j * sprite_size_ + reels_offset_.y;
            window_->draw(curent_sprite, sf::RenderStates().transform.translate({x_pos, y_pos}));
        }
    }

    window_->draw(*automat_sprite_);
    window_->draw(*button_);

    if (result_ > 0)
    {
        window_->draw(*win_sprite_);
        window_->draw(*win_text_);
    }

    window_->display();
    return clock.restart().asSeconds();
}

bool UserInterface::IsButtonPressed()
{
    return button_->IsButtonPressed(*window_);
}

void UserInterface::SetButtonText(const std::string &new_text)
{
    button_->SetText(new_text);
}

void UserInterface::SetResult(int result)
{
    result_ = result;
    win_text_->setString(std::to_string(result_));

    sf::FloatRect text_bound = win_text_->getLocalBounds();
    win_text_->setOrigin(text_bound.width / 2, text_bound.height);
}

Button::Button(int x_size, int y_size, int x_coordinates, int y_coordinates)
    : was_pressed_(false),
      texture_(std::make_unique<sf::Texture>()),
      text_(std::make_unique<sf::Text>())
{
    font_.loadFromFile("Source/DarkGraffiti-Regular.ttf");

    if (texture_->loadFromFile("Source/Button.png", sf::IntRect({0, 0}, {x_size, y_size})))
    {
        texture_->setSmooth(true);
        sprite_ = std::make_unique<sf::Sprite>(texture_);
        sf::FloatRect bound = sprite_->getLocalBounds();
        sprite_->setOrigin(bound.width / 2, bound.height / 2);
        sprite_->setPosition(x_coordinates, y_coordinates);
    }

    text_->setString("START");
    text_->setFont(font_);
    text_->setFillColor(sf::Color::Black);
    text_->setCharacterSize(64);
    sf::FloatRect bound = text_->getLocalBounds();
    text_->setOrigin(bound.width / 2, bound.height / 2 + 10);
    text_->setPosition(x_coordinates, y_coordinates);
}

bool Button::IsButtonPressed(const sf::Window &window)
{
    bool now_pressed = sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
                           sprite_->getGlobalBounds().contains(sf::Mouse::getPosition(window).x,
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
    target.draw(*sprite_, states);
    target.draw(*text_, states);
}

void Button::SetText(const std::string &new_text)
{
    text_->setString(new_text);
    sf::FloatRect bound = text_->getLocalBounds();
    text_->setOrigin(bound.width / 2, bound.height / 2 + 10);
}
