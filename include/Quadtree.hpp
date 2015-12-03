#ifndef QUADTREE_H
#define QUADTREE_H

#include <list>
#include "Structure.hpp"


class Quadtree
{

    public:
        Quadtree();
        Quadtree(std::list<sf::Sprite*> obj);
        virtual ~Quadtree();
        void addObject(std::list<sf::Sprite*> obj);
        void delObjectAt(sf::Vector2f pos);
    protected:
    private:
        QuadTree* m_quadtree;
};

#endif // QUADTREE_H
