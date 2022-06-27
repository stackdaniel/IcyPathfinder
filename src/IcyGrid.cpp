#include "IcyGrid.h"

IcyGrid::IcyGrid(int width_, int height_, int posX, int posY) {
    create(width_, height_, posX, posY);
}

void IcyGrid::create(int width_, int height_, int posX, int posY)
{
    width = width_;
    height = height_;
    texture.loadFromMemory(resources::gridTexturesData, sizeof(resources::gridTexturesData));
    squares = std::vector<std::vector<char>>(height, std::vector<char>(width, ICE_SQUARE));
    gridPos = sf::Vector2i(posX, posY);
    highlighted = sf::Vector2i(-1, -1);
}

void IcyGrid::setHighlighted(sf::Vector2i highlighted_) {
    highlighted = highlighted_;
}

void IcyGrid::setBorderToObstacles()
{
    std::fill(squares[0].begin(), squares[0].end(), OBSTACLE_SQUARE);
    std::fill(squares[getMaxY()].begin(), squares[getMaxY()].end(), OBSTACLE_SQUARE);

    for(int y = 1; y < height - 1; y++) {
        squares[y][0] = OBSTACLE_SQUARE;
        squares[y][width - 1] = OBSTACLE_SQUARE;
    }
}

bool IcyGrid::shrinkX()
{
    if(width <= 2)
        return false;
    for(int y = 0; y < height; y++) {
        squares[y][width - 2] = squares[y][width - 1];
        squares[y].pop_back();
    }
    width--;
    return true;
}

bool IcyGrid::growX()
{
    if(width < 1)
        return false;
    for(int y = 0; y < height; y++) {
        squares[y].push_back(squares[y].back());
        if(y > 0 && y < height - 1)
            squares[y][width - 1] = ICE_SQUARE;
        else
            squares[y][width - 1] = OBSTACLE_SQUARE;
    }
    width++;
    return true;
}

bool IcyGrid::shrinkY()
{
    if(height <= 2)
        return false;
    squares[height - 2] = squares[height - 1];
    squares.pop_back();
    height--;
    return true;
}

bool IcyGrid::growY()
{
    if(height < 1)
        return false;
    squares.push_back(squares.back());
    for(int x = 1; x < width - 1; x++)
        squares[height - 1][x] = ICE_SQUARE;
    squares[height - 1][0] = OBSTACLE_SQUARE;
    squares[height - 1].back() = OBSTACLE_SQUARE;
    height++;
    return true;
}

sf::IntRect IcyGrid::textureRectFromSquareValue(int value)
{
    switch(value) {
    case ICE_SQUARE:
        return sf::IntRect(0, 0, 16, 16);
    case OBSTACLE_SQUARE:
        return sf::IntRect(16, 0, 16, 16);
    case EMPTY_SOLID_SQUARE:
        return sf::IntRect(32, 0, 16, 16);
    case GOAL_SQUARE:
        return sf::IntRect(48, 0, 16, 16);
    case START_SQUARE:
        return sf::IntRect(64, 0, 16, 16);
    }
    return sf::IntRect(32, 0, 16, 16);
}

void IcyGrid::setSquareIce(int x, int y) {
    squares[y][x] = ICE_SQUARE;
}

void IcyGrid::setSquareObstacle(int x, int y) {
    squares[y][x] = OBSTACLE_SQUARE;
}

void IcyGrid::setSquareEmptySolid(int x, int y) {
    squares[y][x] = EMPTY_SOLID_SQUARE;
}

void IcyGrid::setSquareStart(int x, int y) {
    squares[y][x] = START_SQUARE;
}

void IcyGrid::setSquareGoal(int x, int y) {
    squares[y][x] = GOAL_SQUARE;
}

bool IcyGrid::isObstacle(int x, int y) {
    return squares[y][x] == OBSTACLE_SQUARE;
}

bool IcyGrid::isGoal(int x, int y) {
    return squares[y][x] == GOAL_SQUARE;
}

bool IcyGrid::isSolid(int x, int y) {
    return (squares[y][x] == EMPTY_SOLID_SQUARE || squares[y][x] == START_SQUARE || squares[y][x] == GOAL_SQUARE);
}

void IcyGrid::toggleIceOther(int x, int y, int type) {
    if(squares[y][x] == ICE_SQUARE)
        squares[y][x] = type;
    else if(squares[y][x] == type)
        squares[y][x] = ICE_SQUARE;
}

void IcyGrid::swapStartAndGoal() {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if(squares[y][x] == START_SQUARE)
                squares[y][x] = GOAL_SQUARE;
            else if(squares[y][x] == GOAL_SQUARE)
                squares[y][x] = START_SQUARE;
        }
    }
}

int IcyGrid::slideDistMinusX(int x, int y) {
    int dist = 0;
    while(x > 0 && !isObstacle(x - 1, y)) {
        x--;
        dist++;
        if(isSolid(x, y))
            break;
    }
    return dist;
}

int IcyGrid::slideDistPlusX(int x, int y) {
    int maxX = getMaxX();
    int dist = 0;
    while(x < maxX && !isObstacle(x + 1, y)) {
        x++;
        dist++;
        if(isSolid(x, y))
            break;
    }
    return dist;
}

int IcyGrid::slideDistMinusY(int x, int y) {
    int dist = 0;
    while(y > 0 && !isObstacle(x, y - 1)) {
        y--;
        dist++;
        if(isSolid(x, y))
            break;
    }
    return dist;
}

int IcyGrid::slideDistPlusY(int x, int y) {
    int maxY = getMaxY();
    int dist = 0;
    while(y < maxY && !isObstacle(x, y + 1)) {
        y++;
        dist++;
        if(isSolid(x, y))
            break;
    }
    return dist;
}

sf::Vector2i IcyGrid::gridCoordFromWindow(int x, int y)
{
    x -= gridPos.x;
    y -= gridPos.y;

    if(x < 0 || y < 0)
        return sf::Vector2i(-1, -1);

    x /= 32;
    y /= 32;

    if(x > getMaxX() || y > getMaxY())
        return sf::Vector2i(-1, -1);

    return sf::Vector2i(x, y);
}

std::vector<sf::Vector2i> IcyGrid::getAllStartPoints() {
    std::vector<sf::Vector2i> output;
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if(squares[y][x] == START_SQUARE)
                output.emplace_back(x, y);
        }
    }
    return output;
}

void IcyGrid::draw(sf::RenderWindow& window)
{
    sf::RectangleShape rectangle(sf::Vector2f(32.0f, 32.0f));
    rectangle.setFillColor(sf::Color::White);
    rectangle.setTexture(&texture);

    const float baseX = (float)gridPos.x;
    const float baseY = (float)gridPos.y;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            rectangle.setPosition(baseX + (float)x * 32.0f, baseY + (float)y * 32.0f);
            rectangle.setTextureRect(textureRectFromSquareValue(squares[y][x]));
            window.draw(rectangle);
        }
    }

    if(highlighted.x >= 0) {
        rectangle.setOutlineThickness(4.0f);
        rectangle.setOutlineColor(sf::Color(255U, 255U, 255U, 150U));
        rectangle.setPosition(baseX + (float)highlighted.x * 32.0f, baseY + (float)highlighted.y * 32.0f);
        rectangle.setTextureRect(textureRectFromSquareValue(squares[highlighted.y][highlighted.x]));
        window.draw(rectangle);
    }
}

int IcyGrid::getWidth() {
    return width;
}

int IcyGrid::getHeight() {
    return height;
}

int IcyGrid::getMaxX() {
    return width - 1;
}

int IcyGrid::getMaxY() {
    return height - 1;
}

sf::Vector2i IcyGrid::getGridPos() {
    return gridPos;
}

void IcyGrid::saveToFile(std::string filename) {
    std::ofstream fout(filename);
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++)
            fout << (char)(squares[y][x] + 'a');
        fout << "\n";
    }
    fout.close();
}

void IcyGrid::loadFromFile(std::string filename) {
    std::ifstream fin(filename);
    if(!fin)
        return;

    squares.clear();
    std::string fileinput;

    while(!fin.eof()) {
        std::getline(fin, fileinput);

        if(fileinput.size()) {
            squares.push_back(std::vector<char>(fileinput.size()));
            for(unsigned int i = 0; i < fileinput.size(); i++)
                squares.back()[i] = fileinput[i] - 'a';
        }
    }
    fin.close();
    height = squares.size();
    width = squares[0].size();
}