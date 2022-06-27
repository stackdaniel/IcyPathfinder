#ifndef ICE_PATHFINDER_WINDOW_H
#define ICE_PATHFINDER_WINDOW_H

#include<memory>
#include<SFML/Graphics.hpp>

#include "resources/imageTextureData.h"
#include "resources/fontData.h"

#include "saveOpenFiles.h"
#include "IcyGrid.h"
#include "GridPath.h"

#include "controls/BorderBox.h"
#include "controls/ButtonGroup.h"
#include "controls/TextGroup.h"

class IcyPathfinderWindow
{
    const int borderSize = 32 * 3;

    sf::RenderWindow window;
    sf::Color backgroundColor;

    IcyGrid icyGrid;
    ButtonGroup buttons;
    TextGroup text;

    BorderBox fileButtonBorder;
    BorderBox selectorButtonBorder;

    bool updatePath;
    GridPath gridPathShortest;
    GridPath gridPathFewest;

    sf::Texture gridTexture;
    sf::Texture arrowButtonTextures;
    sf::Texture fileButtonTextures;

    int squareTypeToPlace;
    BorderBox selectorBorder;

public:
    IcyPathfinderWindow(int windowWidth, int windowHeight);

    void createGrid();
    void createFileControls();
    void positionSelectorFromType();
    void createSelectorControls();
    void createHeightWidthControls();

    void changeWindowSizeRelative(int xChange, int yChange);

    void rotateSelectedUp();
    void rotateSelectedDown();

    void handleButtonPresses();
    void processEvents();
    void draw();
    bool isOpen();
};

#endif // ICE_PATHFINDER_WINDOW_H