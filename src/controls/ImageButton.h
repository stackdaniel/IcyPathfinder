#ifndef IMAGE_BUTTON_H
#define IMAGE_BUTTON_H

#include "Button.h"

class ImageButton : public Button
{
    typedef Button super;

    sf::Texture texture;
    sf::IntRect textureRect;
    float rotationAngle;

public:
    ImageButton(sf::IntRect region, ButtonIdentifier identifier_ = ButtonIdentifier::NONE) :
        rotationAngle(0.0f), super(region, sf::Color::White, identifier_) {}

    ImageButton(sf::IntRect region, sf::Texture texture_, sf::IntRect textureRect_, float rotationAngle_, ButtonIdentifier identifier_ = ButtonIdentifier::NONE) :
        super(region, sf::Color::White, identifier_)
    {
        setTexture(texture_, textureRect_, rotationAngle_);
    }

    void setTexture(sf::Texture texture_, sf::IntRect textureRect_, float rotationAngle_);
    void draw(sf::RenderWindow& window, sf::RectangleShape rectangle = sf::RectangleShape());
};

#endif // IMAGE_BUTTON_H