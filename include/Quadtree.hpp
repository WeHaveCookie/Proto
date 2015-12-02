#ifndef QUADTREE_H
#define QUADTREE_H
#include "Structure.hpp"

class Quadtree
{

    public:
        Quadtree();
        Quadtree(list<sf::Sprite*> obj);
        virtual ~Quadtree();
        void addObject(list<sf::Sprite*> obj);
        void delObjectAt(sf::Vector2f pos);
    protected:
    private:
        QuadTree* m_quadtree;
};

#endif // QUADTREE_H
