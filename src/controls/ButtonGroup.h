#ifndef BUTTON_GROUP_H
#define BUTTON_GROUP_H

#include<vector>
#include<SFML/Graphics.hpp>

#include "Button.h"
#include "ImageButton.h"

class ButtonGroup
{
    std::vector<std::unique_ptr<Button>> buttons;
public:

    void addButton(sf::IntRect region, sf::Color color, ButtonIdentifier identifier);
    void addImageButton(sf::IntRect region, sf::Texture texture, sf::IntRect textureRect, float rotationAngle, ButtonIdentifier identifier);
    void draw(sf::RenderWindow& window);
    ButtonIdentifier getClickedButton(sf::Vector2i& mousePosition);
};

#endif // BUTTON_GROUP_H