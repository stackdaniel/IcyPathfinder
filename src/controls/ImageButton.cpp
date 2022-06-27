#include "ImageButton.h"

void ImageButton::setTexture(sf::Texture texture_, sf::IntRect textureRect_, float rotationAngle_)
{
    texture = texture_;
    textureRect = textureRect_;
    rotationAngle = rotationAngle_;
}

void ImageButton::draw(sf::RenderWindow& window, sf::RectangleShape rectangle)
{
    rectangle.setTexture(&texture);
    rectangle.setTextureRect(textureRect);
    rectangle.setRotation(rotationAngle);

    super::draw(window, rectangle);
}