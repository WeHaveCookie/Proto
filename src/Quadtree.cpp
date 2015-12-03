#include "Quadtree.hpp"

Quadtree::Quadtree()
{
    m_quadtree = new QuadTree;
}

Quadtree::~Quadtree()
{

}

/**
*
* \fn Quadtree(std::list<sf::Sprite*> obj)
*
* \brief Built a Quadtree with a existing Segment
*
* \param obj : List of Object
* \return none. Built the Quadtree which matching to segment
**/
Quadtree::Quadtree(std::list<sf::Sprite*> obj)
{

}

/**
*
* \fn addObject(std::list<sf::Sprite*> obj)
*
* \brief Add a object to the Quadtree
*
* \param obj : Object to be add
* \return Void
**/
void Quadtree::addObject(std::list<sf::Sprite*> obj)
{

}

/**
*
* \fn delObjectAt(sf::Vector2f pos)
*
* \brief Delete a object from Quadtree at position pos
*
* \param pos : The position of the object to be deleted
* \return void
**/
void Quadtree::delObjectAt(sf::Vector2f pos)
{

}
