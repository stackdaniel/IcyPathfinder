#include "TextGroup.h"

void TextGroup::create(sf::Font font_, int characterSize_, sf::Color color_)
{
    font = font_;
    characterSize = characterSize_;
    color = color_;
}

void TextGroup::addText(std::string textString, int xPos, int yPos, float rotation)
{
    text.push_back(std::make_unique<sf::Text>());

    text.back()->setFont(font);
    text.back()->setCharacterSize(characterSize);
    text.back()->setFillColor(color);

    text.back()->setString(textString);
    text.back()->setPosition((float)xPos, (float)yPos);
    text.back()->setRotation(rotation);
}

void TextGroup::draw(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < text.size(); i++)
        window.draw(*text[i]);
}