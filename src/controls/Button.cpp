#include "Button.h"

void Button::draw(sf::RenderWindow& window, sf::RectangleShape rectangle)
{
    float halfWidth = (float)region.width / 2.0f;
    float halfHeight = (float)region.height / 2.0f;

    rectangle.setFillColor(color);
    rectangle.setPosition(sf::Vector2f((float)region.left + halfWidth, (float)region.top + halfHeight));
    rectangle.setSize(sf::Vector2f((float)region.width, (float)region.height));
    rectangle.setOrigin(halfWidth, halfHeight);

    window.draw(rectangle);
}

bool Button::inArea(sf::Vector2i& point) {
    return region.contains(point);
}

ButtonIdentifier Button::getIdentifier() {
    return identifier;
}