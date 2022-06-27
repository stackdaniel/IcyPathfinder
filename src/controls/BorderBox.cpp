#include "BorderBox.h"

void BorderBox::create(sf::IntRect region_, float thickness_, sf::Color color_)
{
    region = region_;
    thickness = thickness_;
    color = color_;
}

void BorderBox::setRect(sf::IntRect region_) {
    region = region_;
}

void BorderBox::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle;

    rectangle.setPosition(sf::Vector2f((float)region.left, (float)region.top));
    rectangle.setSize(sf::Vector2f((float)region.width, (float)region.height));

    rectangle.setFillColor(sf::Color(0U, 0U, 0U, 0U));
    rectangle.setOutlineThickness(thickness);
    rectangle.setOutlineColor(color);

    window.draw(rectangle);
}