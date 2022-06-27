#include "ButtonGroup.h"

void ButtonGroup::addButton(sf::IntRect region, sf::Color color, ButtonIdentifier identifier) {
    buttons.push_back(std::make_unique<Button>(region, color, identifier));
}

void ButtonGroup::addImageButton(sf::IntRect region, sf::Texture texture, sf::IntRect textureRect, float rotationAngle, ButtonIdentifier identifier) {
    buttons.push_back(std::make_unique<ImageButton>(region, texture, textureRect, rotationAngle, identifier));
}

void ButtonGroup::draw(sf::RenderWindow& window)
{
    for(unsigned int i = 0; i < buttons.size(); i++)
        buttons[i]->draw(window);
}

ButtonIdentifier ButtonGroup::getClickedButton(sf::Vector2i& mousePosition)
{
    for(unsigned int i = 0; i < buttons.size(); i++) {
        if(buttons[i]->inArea(mousePosition))
            return buttons[i]->getIdentifier();
    }
    return ButtonIdentifier::NONE;
}