#ifndef STRUCTURE_H
#define STRUCTURE_H


struct AABB
{
    float x;
    float y;
    float w;
    float h;
};

struct QuadTree
{
    AABB bbox;
    QuadTree* child[4];
    list<sf::Sprite*> objects;
};


#endif // STRUCTURE_H
