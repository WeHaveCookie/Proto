#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "Structure.hpp"
#include "Engine.hpp"


class Quadtree
{

    public:
        Quadtree();
        Quadtree(std::vector<sf::Sprite*> obj);
        virtual ~Quadtree();
        bool add(sf::Sprite* obj);
        bool del(sf::Vector2f pos);
        std::vector<sf::Sprite*>  queryRange(sf::Sprite* obj);
    protected:
    private:
        void subdivide();

        QuadTree* m_northWest;
        QuadTree* m_northEast;
        QuadTree* m_southWest;
        QuadTree* m_southEast;
        std::vector<sf::Sprite*> m_elements;
        sf::FloatRect m_boundary;
};

#endif // QUADTREE_H
