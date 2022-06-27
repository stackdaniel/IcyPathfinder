#include "IcyPathfinderWindow.h"

IcyPathfinderWindow::IcyPathfinderWindow(int windowWidth, int windowHeight)
{
    window.create(sf::VideoMode(windowWidth, windowHeight), "Icy Pathfinder", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(true);

    backgroundColor = sf::Color(30, 30, 30);
    updatePath = true;

    squareTypeToPlace = IcyGrid::OBSTACLE_SQUARE;

    gridPathShortest.setColor(sf::Color(200U, 0U, 0U, 100U));
    gridPathFewest.setColor(sf::Color(250U, 100U, 0U, 100U));

    gridTexture.loadFromMemory(resources::gridTexturesData, sizeof(resources::gridTexturesData));
    arrowButtonTextures.loadFromMemory(resources::arrowTextureData, sizeof(resources::arrowTextureData));
    fileButtonTextures.loadFromMemory(resources::fileIconTextureData, sizeof(resources::fileIconTextureData));

    sf::Font font;
    font.loadFromMemory(resources::boldFontData, sizeof(resources::boldFontData));
    text.create(font, 20, sf::Color(220U, 220U, 220U));

    createGrid();
    createFileControls();
    createSelectorControls();
    createHeightWidthControls();
}

void IcyPathfinderWindow::createGrid()
{
    icyGrid.create(20, 10, borderSize, borderSize + 32);

    icyGrid.setBorderToObstacles();
    icyGrid.setSquareObstacle(10, 7);
    icyGrid.setSquareObstacle(11, 2);

    icyGrid.setSquareStart(0, 1);
    icyGrid.setSquareStart(0, 2);
    icyGrid.setSquareGoal(icyGrid.getMaxX(), 6);
    icyGrid.setSquareGoal(icyGrid.getMaxX(), 7);
}

void IcyPathfinderWindow::createFileControls()
{
    int baseX = 20;
    int baseY = 20;

    fileButtonBorder.create(sf::IntRect(baseX, baseY, 128, 46), 3.0f, sf::Color(75U, 75U, 75U));

    buttons.addImageButton(sf::IntRect(baseX + 5, baseY + 5, 36, 36), fileButtonTextures, sf::IntRect(18, 0, 18, 18), 0.0f, ButtonIdentifier::SAVE);
    buttons.addImageButton(sf::IntRect(baseX + 46, baseY + 5, 36, 36), fileButtonTextures, sf::IntRect(0, 0, 18, 18), 0.0f, ButtonIdentifier::LOAD);
    buttons.addImageButton(sf::IntRect(baseX + 87, baseY + 5, 36, 36), fileButtonTextures, sf::IntRect(36, 0, 18, 18), 0.0f, ButtonIdentifier::SWAP);
}

void IcyPathfinderWindow::positionSelectorFromType()
{
    int offset = 0;

    if(squareTypeToPlace == IcyGrid::OBSTACLE_SQUARE)
        offset = 0;
    else if(squareTypeToPlace == IcyGrid::EMPTY_SOLID_SQUARE)
        offset = 39;
    else if(squareTypeToPlace == IcyGrid::START_SQUARE)
        offset = 78;
    else if(squareTypeToPlace == IcyGrid::GOAL_SQUARE)
        offset = 117;

    selectorBorder.setRect(sf::IntRect(200 + offset, 25, 36, 36));
}

void IcyPathfinderWindow::createSelectorControls()
{
    int baseX = 195;
    int baseY = 27;

    selectorButtonBorder.create(sf::IntRect(baseX, baseY - 7, 163, 46), 3.0f, sf::Color(75U, 75U, 75U));

    buttons.addImageButton(sf::IntRect(baseX + 7, baseY, 32, 32), gridTexture, icyGrid.textureRectFromSquareValue(IcyGrid::OBSTACLE_SQUARE),
        0.0f, ButtonIdentifier::SELECT_OBSTACLE);
    buttons.addImageButton(sf::IntRect(baseX + 46, baseY, 32, 32), gridTexture, icyGrid.textureRectFromSquareValue(IcyGrid::EMPTY_SOLID_SQUARE),
        0.0f, ButtonIdentifier::SELECT_SOLID);
    buttons.addImageButton(sf::IntRect(baseX + 85, baseY, 32, 32), gridTexture, icyGrid.textureRectFromSquareValue(IcyGrid::START_SQUARE),
        0.0f, ButtonIdentifier::SELECT_START);
    buttons.addImageButton(sf::IntRect(baseX + 124, baseY, 32, 32), gridTexture, icyGrid.textureRectFromSquareValue(IcyGrid::GOAL_SQUARE),
        0.0f, ButtonIdentifier::SELECT_GOAL);

    selectorBorder.create(sf::IntRect(baseX, baseY, 36, 36), 4.0f, sf::Color(255U, 255U, 255U, 180U));
    positionSelectorFromType();
}

void IcyPathfinderWindow::createHeightWidthControls()
{
    int baseX = 55;
    int baseY = 87;

    text.addText("WIDTH", baseX + 135, baseY + 1);
    text.addText("HEIGHT", baseX + 1, baseY + 201, -90.0f);

    buttons.addImageButton(sf::IntRect(baseX + 55, baseY, 27, 27), arrowButtonTextures, sf::IntRect(0, 0, 9, 9), 180.0f, ButtonIdentifier::SHRINK_X);
    buttons.addImageButton(sf::IntRect(baseX + 95, baseY, 27, 27), arrowButtonTextures, sf::IntRect(0, 0, 9, 9), 0.0f, ButtonIdentifier::GROW_X);
    buttons.addImageButton(sf::IntRect(baseX, baseY + 55, 27, 27), arrowButtonTextures, sf::IntRect(0, 0, 9, 9), 270.0f, ButtonIdentifier::SHRINK_Y);
    buttons.addImageButton(sf::IntRect(baseX, baseY + 95, 27, 27), arrowButtonTextures, sf::IntRect(0, 0, 9, 9), 90.0f, ButtonIdentifier::GROW_Y);
}

void IcyPathfinderWindow::changeWindowSizeRelative(int xChange, int yChange)
{
    sf::Vector2u windowSize = window.getSize();
    windowSize.x += xChange;
    windowSize.y += yChange;
    window.setSize(windowSize);
}

void IcyPathfinderWindow::rotateSelectedUp()
{
    if(squareTypeToPlace == IcyGrid::OBSTACLE_SQUARE)
        squareTypeToPlace = IcyGrid::GOAL_SQUARE;
    else if(squareTypeToPlace == IcyGrid::GOAL_SQUARE)
        squareTypeToPlace = IcyGrid::START_SQUARE;
    else if(squareTypeToPlace == IcyGrid::START_SQUARE)
        squareTypeToPlace = IcyGrid::EMPTY_SOLID_SQUARE;
    else if(squareTypeToPlace == IcyGrid::EMPTY_SOLID_SQUARE)
        squareTypeToPlace = IcyGrid::OBSTACLE_SQUARE;
}

void IcyPathfinderWindow::rotateSelectedDown()
{
    if(squareTypeToPlace == IcyGrid::OBSTACLE_SQUARE)
        squareTypeToPlace = IcyGrid::EMPTY_SOLID_SQUARE;
    else if(squareTypeToPlace == IcyGrid::EMPTY_SOLID_SQUARE)
        squareTypeToPlace = IcyGrid::START_SQUARE;
    else if(squareTypeToPlace == IcyGrid::START_SQUARE)
        squareTypeToPlace = IcyGrid::GOAL_SQUARE;
    else if(squareTypeToPlace == IcyGrid::GOAL_SQUARE)
        squareTypeToPlace = IcyGrid::OBSTACLE_SQUARE;
}

void IcyPathfinderWindow::handleButtonPresses()
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    ButtonIdentifier buttonPressed = buttons.getClickedButton(mousePosition);

    switch(buttonPressed)
    {
    case ButtonIdentifier::SHRINK_X:
        updatePath = true;
        if(icyGrid.shrinkX())
            changeWindowSizeRelative(-32, 0);
        break;
    case ButtonIdentifier::GROW_X:
        updatePath = true;
        if(icyGrid.growX())
            changeWindowSizeRelative(32, 0);
        break;
    case ButtonIdentifier::SHRINK_Y:
        updatePath = true;
        if(icyGrid.shrinkY())
            changeWindowSizeRelative(0, -32);
        break;
    case ButtonIdentifier::GROW_Y:
        updatePath = true;
        if(icyGrid.growY())
            changeWindowSizeRelative(0, 32);
        break;
    case ButtonIdentifier::SAVE:
        icyGrid.saveToFile(saveFilename(".txt", "Text File", NULL));
        break;
    case ButtonIdentifier::LOAD:
    {
        updatePath = true;
        sf::Vector2i oldGridSize(icyGrid.getWidth(), icyGrid.getHeight());
        icyGrid.loadFromFile(openFilename(".txt", "Text File", NULL));
        sf::Vector2i newGridSize(icyGrid.getWidth(), icyGrid.getHeight());
        changeWindowSizeRelative((newGridSize.x - oldGridSize.x) * 32, (newGridSize.y - oldGridSize.y) * 32);
        break;
    }
    case ButtonIdentifier::SWAP:
        icyGrid.swapStartAndGoal();
        updatePath = true;
        break;
    case ButtonIdentifier::SELECT_OBSTACLE:
        squareTypeToPlace = IcyGrid::OBSTACLE_SQUARE;
        positionSelectorFromType();
        break;
    case ButtonIdentifier::SELECT_SOLID:
        squareTypeToPlace = IcyGrid::EMPTY_SOLID_SQUARE;
        positionSelectorFromType();
        break;
    case ButtonIdentifier::SELECT_START:
        squareTypeToPlace = IcyGrid::START_SQUARE;
        positionSelectorFromType();
        break;
    case ButtonIdentifier::SELECT_GOAL:
        squareTypeToPlace = IcyGrid::GOAL_SQUARE;
        positionSelectorFromType();
        break;
    }
}

void IcyPathfinderWindow::processEvents()
{
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed)
            window.close();
        else if(event.type == sf::Event::Resized) {
            sf::FloatRect visibleArea(0, 0, (float)event.size.width, (float)event.size.height);
            window.setView(sf::View(visibleArea));
        }
        else if(event.type == sf::Event::MouseMoved) {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            sf::Vector2i gridCoord = icyGrid.gridCoordFromWindow(localPosition.x, localPosition.y);
            icyGrid.setHighlighted(gridCoord);
        }
        else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            handleButtonPresses();

            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            sf::Vector2i gridCoord = icyGrid.gridCoordFromWindow(mousePosition.x, mousePosition.y);

            if(gridCoord.x >= 0) {
                icyGrid.toggleIceOther(gridCoord.x, gridCoord.y, squareTypeToPlace);
                updatePath = true;
            }
        }
        else if(event.type == sf::Event::MouseWheelScrolled) {
            int ticks = (int)event.mouseWheelScroll.delta;

            while(ticks > 0) {
                rotateSelectedUp();
                ticks--;
            }
            while(ticks < 0) {
                rotateSelectedDown();
                ticks++;
            }
            positionSelectorFromType();
        }
    }

    if(updatePath) {
        gridPathShortest.setToShortestDistance(icyGrid);
        gridPathFewest.setToFewestSteps(icyGrid);

        if(gridPathFewest.getPointCount() == gridPathShortest.getPointCount())
            gridPathFewest.copyPoints(gridPathShortest);
        else if(gridPathFewest.getDistance() == gridPathShortest.getDistance())
            gridPathShortest.copyPoints(gridPathFewest);

        updatePath = false;
    }
}

void IcyPathfinderWindow::draw()
{
    window.clear(backgroundColor);

    icyGrid.draw(window);
    gridPathShortest.draw(window, icyGrid.getGridPos());
    gridPathFewest.draw(window, icyGrid.getGridPos());

    buttons.draw(window);
    text.draw(window);

    selectorBorder.draw(window);
    fileButtonBorder.draw(window);
    selectorButtonBorder.draw(window);

    window.display();
}

bool IcyPathfinderWindow::isOpen() {
    return window.isOpen();
}