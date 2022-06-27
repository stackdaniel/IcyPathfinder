#ifndef ICY_GRID_H
#define ICY_GRID_H

#include<fstream>
#include<vector>
#include<SFML/Graphics.hpp>

#include "resources/imageTextureData.h"

class IcyGrid
{
    int width;
    int height;
    sf::Vector2i gridPos;
    sf::Vector2i highlighted;
    std::vector<std::vector<char>> squares;
    sf::Texture texture;

public:
    IcyGrid() {}
    IcyGrid(int width_, int height_, int posX, int posY);

    void create(int width_, int height_, int posX, int posY);

    void setHighlighted(sf::Vector2i highlighted_);

    void setBorderToObstacles();

    bool shrinkX();
    bool growX();
    bool shrinkY();
    bool growY();

    sf::IntRect textureRectFromSquareValue(int value);

    void setSquareIce(int x, int y);
    void setSquareObstacle(int x, int y);
    void setSquareEmptySolid(int x, int y);
    void setSquareStart(int x, int y);
    void setSquareGoal(int x, int y);

    bool isObstacle(int x, int y);
    bool isGoal(int x, int y);
    bool isSolid(int x, int y);

    void toggleIceOther(int x, int y, int type);
    void swapStartAndGoal();

    int slideDistMinusX(int x, int y);
    int slideDistPlusX(int x, int y);
    int slideDistMinusY(int x, int y);
    int slideDistPlusY(int x, int y);

    sf::Vector2i gridCoordFromWindow(int x, int y);

    std::vector<sf::Vector2i> getAllStartPoints();

    void draw(sf::RenderWindow& window);

    int getWidth();
    int getHeight();
    int getMaxX();
    int getMaxY();

    sf::Vector2i getGridPos();

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);

    static const char ICE_SQUARE = 0;
    static const char OBSTACLE_SQUARE = 1;
    static const char EMPTY_SOLID_SQUARE = 2;
    static const char START_SQUARE = 3;
    static const char GOAL_SQUARE = 4;
};

#endif // ICY_GRID_H