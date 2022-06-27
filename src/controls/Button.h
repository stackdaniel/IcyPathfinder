#ifndef BUTTON_H
#define BUTTON_H

#include<SFML/Graphics.hpp>

enum class ButtonIdentifier
{
    NONE,
    SHRINK_X,
    GROW_X,
    SHRINK_Y,
    GROW_Y,
    SAVE,
    LOAD,
    SWAP,
    SELECT_OBSTACLE,
    SELECT_SOLID,
    SELECT_START,
    SELECT_GOAL
};

class Button
{
protected:
    sf::Color color;
    sf::IntRect region;
    ButtonIdentifier identifier;

public:
    Button(sf::IntRect region, sf::Color color_, ButtonIdentifier identifier_ = ButtonIdentifier::NONE) :
        region(region), color(color_), identifier(identifier_) {}

    virtual void draw(sf::RenderWindow& window, sf::RectangleShape rectangle = sf::RectangleShape());
    bool inArea(sf::Vector2i& point);
    ButtonIdentifier getIdentifier();
};

#endif // BUTTON_H
