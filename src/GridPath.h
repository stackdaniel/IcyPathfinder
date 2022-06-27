#ifndef GRID_PATH_H
#define GRID_PATH_H

#include<vector>
#include<queue>
#include<SFML/Graphics.hpp>

#include "IcyGrid.h"

class GridPath
{
    class SearchPath
    {
    public:
        SearchPath(sf::Vector2i point_);
        SearchPath(SearchPath& prevPath, int x, int y, int addDist);

        friend bool operator > (const SearchPath& a, const SearchPath& b) {
            return a.dist > b.dist;
        }

        sf::Vector2i point;
        int dist;
        std::vector<sf::Vector2i> toReach;
    };

    template<class queueContainer>
    void spreadPath(SearchPath& thisPath, queueContainer& pathQueue, IcyGrid& grid);

    SearchPath searchQueueNext(std::queue<SearchPath> pathQueue);
    SearchPath searchQueueNext(std::priority_queue<SearchPath, std::vector<SearchPath>, std::greater<SearchPath>> pathQueue);

    template<class queueContainer>
    void setToGenericBestPath(IcyGrid& grid, queueContainer& pathQueue);

    float displaySize(int input);

    sf::Color color;
    std::vector<sf::Vector2i> points;
    int distance;

public:
    GridPath() : distance(0) {}
    GridPath(sf::Color color_) : color(color_), distance(0) {}

    void setColor(sf::Color color_);

    int getPointCount();
    int getDistance();

    void copyPoints(GridPath& other);
    void addPoint(int x, int y);

    void setToShortestDistance(IcyGrid& grid);
    void setToFewestSteps(IcyGrid& grid);

    void draw(sf::RenderWindow& window, sf::Vector2i gridPos);
};

#endif // GRID_PATH_H