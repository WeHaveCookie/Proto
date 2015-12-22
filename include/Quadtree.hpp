#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Structure.hpp"
#include "Constante.hpp"
//#include "Engine.hpp"

#define DEBUG 1
class Quadtree
{

    public:
        Quadtree(float x, float y, float width, float height);
        ~Quadtree();
        //Quadtree(std::vector<sf::Sprite*> obj);
        //virtual ~Quadtree();
        bool add(sf::Sprite* obj);
        sf::Sprite* del(sf::Vector2f pos);
        std::vector<sf::Sprite*>*  queryRange(sf::Vector2f pos);
        inline sf::FloatRect getShape() {return m_shape;}

        void clear();
        void draw(sf::RenderWindow* window);
        void displayTile(bool b);
        inline bool isDisplayTile() {return m_displayTile;}

    protected:
        inline bool isEmpty() {return m_elements->empty();}
        int nbElement();
        inline std::vector<sf::Sprite*>* getElements() {return m_elements;}
    private:
        void subdivide();
        void merge();
        Quadtree* m_northWest;
        Quadtree* m_northEast;
        Quadtree* m_southWest;
        Quadtree* m_southEast;
        std::vector<sf::Sprite*>* m_elements;
        sf::RectangleShape m_boundary;
        sf::FloatRect m_shape;
        bool m_enable;
        bool m_displayTile;
};

#endif // QUADTREE_H
