#include "../include/Engine.hpp"

Engine::Engine()
{
    //ctor
}

Engine::~Engine()
{
    //dtor
}

/**
* \fn collisionAABB(sf::FloatRect box1, sf::FloatRect box2)
*
* \brief Detect collission between box1 and box2
*
* \param box1 : The first AABB, box2 : The second AABB
* \return Return True if there is a collision between the 2 box. False otherwise
**/
bool Engine::collisionAABB(sf::FloatRect box1, sf::FloatRect box2)
{
    return (box2.left >= box1.left + box1.width) ||
        (box2.left  + box2.width <= box1.width) ||
        (box2.top >= box1.top + box1.height) ||
        (box2.top + box2.height <= box1.top);
}

/**
* \fn move(sf::FloatRect box1, sf::Vector2f motion)
*
* \brief Try if box1 can move correctly by motion
*
* \param box1 : The AABB to test, motion : Motion Vector, universe : Quadtree which represents world
* \return True if the movement of box1 by motion is correct. False otherwise
**/
bool Engine::move(sf::FloatRect box1, sf::Vector2f motion, Quadtree* universe)
{// TODO
    return true;
}

/**
* \fn jump(sf::FloatRect box1, sf::Vector2f motion)
*
* \brief Try if box1 can jump correctly by motion
*
* \param box1 : The AABB to test, motion : Motion Vector, universe : Quadtree which represents world
* \return True if the movement of box1 by motion is correct. False otherwise
**/
/*bool Engine::jump(sf::FloatRect box1, sf::Vector2f motion, Quadtree* universe)
{

}*/
