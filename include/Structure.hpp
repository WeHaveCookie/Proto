#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
#include <SFML/Graphics.hpp>

/*
struct QuadTree
{
    sf::Vector2f bbox;
    QuadTree* child[4];
    std::list<sf::Sprite*> objects;
};*/

struct SplitedSprite
{
    sf::Sprite* origin;
    sf::Sprite* NW;
    sf::Sprite* NE;
    sf::Sprite* SW;
    sf::Sprite* SE;
};

#endif // STRUCTURE_H
