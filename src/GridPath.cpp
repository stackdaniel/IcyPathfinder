#include "GridPath.h"

GridPath::SearchPath::SearchPath(sf::Vector2i point_) : point(point_), dist(0) {
    toReach.emplace_back(point);
}

GridPath::SearchPath::SearchPath(GridPath::SearchPath& prevPath, int x, int y, int addDist)
{
    point = sf::Vector2i(x, y);
    dist = prevPath.dist + addDist;
    toReach = prevPath.toReach;
    toReach.emplace_back(x, y);
}

template<class queueContainer>
void GridPath::spreadPath(SearchPath& thisPath, queueContainer& pathQueue, IcyGrid& grid)
{
    int dist = grid.slideDistMinusX(thisPath.point.x, thisPath.point.y);
    if(dist > 0)
        pathQueue.emplace(thisPath, thisPath.point.x - dist, thisPath.point.y, dist);

    dist = grid.slideDistPlusX(thisPath.point.x, thisPath.point.y);
    if(dist > 0)
        pathQueue.emplace(thisPath, thisPath.point.x + dist, thisPath.point.y, dist);

    dist = grid.slideDistMinusY(thisPath.point.x, thisPath.point.y);
    if(dist > 0)
        pathQueue.emplace(thisPath, thisPath.point.x, thisPath.point.y - dist, dist);

    dist = grid.slideDistPlusY(thisPath.point.x, thisPath.point.y);
    if(dist > 0)
        pathQueue.emplace(thisPath, thisPath.point.x, thisPath.point.y + dist, dist);
}

GridPath::SearchPath GridPath::searchQueueNext(std::queue<SearchPath> pathQueue) {
    return pathQueue.front();
}

GridPath::SearchPath GridPath::searchQueueNext(std::priority_queue<SearchPath, std::vector<SearchPath>, std::greater<SearchPath>> pathQueue) {
    return pathQueue.top();
}

template<class queueContainer>
void GridPath::setToGenericBestPath(IcyGrid& grid, queueContainer& pathQueue) {
    points.clear();

    for(sf::Vector2i& start : grid.getAllStartPoints())
        pathQueue.emplace(start);

    std::vector<std::vector<bool>> searched(grid.getHeight(), std::vector<bool>(grid.getWidth(), false));

    while(!pathQueue.empty()) {
        SearchPath thisPath = searchQueueNext(pathQueue);
        pathQueue.pop();

        if(searched[thisPath.point.y][thisPath.point.x])
            continue;
        searched[thisPath.point.y][thisPath.point.x] = true;

        if(grid.isGoal(thisPath.point.x, thisPath.point.y)) {
            points = thisPath.toReach;
            distance = thisPath.dist;
            break;
        }

        spreadPath(thisPath, pathQueue, grid);
    }
}

float GridPath::displaySize(int input) {
    return (32.0f * (float)input);
}

void GridPath::setColor(sf::Color color_) {
    color = color_;
}

int GridPath::getPointCount() {
    return points.size();
}

int GridPath::getDistance() {
    return distance;
}

void GridPath::copyPoints(GridPath& other) {
    points = other.points;
}

void GridPath::addPoint(int x, int y) {
    points.emplace_back(x, y);
}

void GridPath::setToShortestDistance(IcyGrid& grid) {
    std::priority_queue<SearchPath, std::vector<SearchPath>, std::greater<SearchPath>> pathPriorityQueue;
    setToGenericBestPath(grid, pathPriorityQueue);
}

void GridPath::setToFewestSteps(IcyGrid& grid) {
    std::queue<SearchPath> pathQueue;
    setToGenericBestPath(grid, pathQueue);
}

void GridPath::draw(sf::RenderWindow& window, sf::Vector2i gridPos)
{
    sf::RectangleShape rectangle(sf::Vector2f(1.0f, 1.0f));
    rectangle.setFillColor(color);

    const float baseX = 12.0f + (float)gridPos.x;
    const float baseY = 12.0f + (float)gridPos.y;

    int pointCount = (signed)points.size();

    for(int i = 0; i < pointCount - 1; i++) {
        sf::Vector2i firstPoint;
        sf::Vector2i secondPoint;

        if(points[i].x <= points[i + 1].x && points[i].y <= points[i + 1].y) {
            firstPoint = points[i];
            secondPoint = points[i + 1];
        }
        else {
            firstPoint = points[i + 1];
            secondPoint = points[i];
        }

        sf::Vector2f size = sf::Vector2f(8.0f + displaySize(secondPoint.x - firstPoint.x), 8.0f + displaySize(secondPoint.y - firstPoint.y));
        rectangle.setSize(size);

        sf::Vector2f position = sf::Vector2f(baseX + displaySize(firstPoint.x), baseY + displaySize(firstPoint.y));
        rectangle.setPosition(position);

        window.draw(rectangle);
    }
}