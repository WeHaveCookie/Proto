#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
#include <SFML/Graphics.hpp>

struct QuadTree
{
    sf::Vector2f bbox;
    QuadTree* child[4];
    std::list<sf::Sprite*> objects;
};



#endif // STRUCTURE_H
