#ifndef TEXT_GROUP_H
#define TEXT_GROUP_H

#include<vector>
#include<SFML/Graphics.hpp>

class TextGroup
{
    sf::Font font;
    int characterSize;
    sf::Color color;
    std::vector<std::unique_ptr<sf::Text>> text;

public:
    TextGroup() {}
    TextGroup(sf::Font font_, int characterSize_, sf::Color color_) : font(font_), characterSize(characterSize_), color(color_) {}

    void create(sf::Font font_, int characterSize_, sf::Color color_);
    void addText(std::string textString, int xPos, int yPos, float rotation = 0.0f);
    void draw(sf::RenderWindow& window);
};

#endif // TEXT_GROUP_H