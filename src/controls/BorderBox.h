#ifndef BORDER_BOX_H
#define BORDER_BOX_H

#include<SFML/Graphics.hpp>

class BorderBox
{
    sf::IntRect region;
    sf::Color color;
    float thickness;

public:
    BorderBox() {}
    BorderBox(sf::IntRect region_, float thickness_, sf::Color color_) : region(region_), thickness(thickness_), color(color_) {}

    void create(sf::IntRect region_, float thickness_, sf::Color color_);
    void setRect(sf::IntRect region_);
    void draw(sf::RenderWindow& window);
};

#endif // BORDER_BOX_H