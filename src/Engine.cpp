#include "../include/Engine.hpp"

Engine::Engine(std::shared_ptr<Quadtree> universe)
{
    m_universe = universe;
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
    return !((box2.left >= box1.left + box1.width) ||
        (box2.left  + box2.width <= box1.left) ||
        (box2.top >= box1.top + box1.height) ||
        (box2.top + box2.height <= box1.top));
}

/**
* \fn move(sf::Sprite box1, sf::Vector2f motion, Quadtree* universe)
*
* \brief Try if box1 can move correctly by motion
*
* \param box1 : The Sprite to test, motion : Motion Vector, universe : Quadtree which represents world
* \return True if the movement of box1 by motion is correct. False otherwise
**/
bool Engine::isAbleToMove(sf::FloatRect box)
{
    if(DEBUG)
    {
        std::cout << "*-----------------*" << std::endl;
        std::cout << "*  ENGINE : MOVE  *" << std::endl;
        std::cout << "*-----------------*" << std::endl;
    }

    std::vector<std::shared_ptr<sf::Sprite>> listObject = m_universe->queryRange(box);
    if(listObject.size() > 0)
    {
        if(DEBUG)
        {
            std::cout << "Il y a " << listObject.size() << " en possible collision" << std::endl;
        }
        for(std::vector<std::shared_ptr<sf::Sprite>>::iterator it = listObject.begin(); it != listObject.end(); it++)
        {
           if(collisionAABB((*it)->getGlobalBounds(),box))
           {
               if(DEBUG)
               {
                   std::cout << "*-----------*" << std::endl;
                   std::cout << "  COLLISION  " << std::endl;
                   std::cout << "*-----------*" << std::endl;
                   std::cout << "Char : [x=" << box.left << ";y=" << box.top << ";width=" << box.width << ";height=" << box.height <<  "]" << std::endl;
                   std::cout << "Tile : [x=" << (*it)->getGlobalBounds().left << ";y=" << (*it)->getGlobalBounds().top << ";width=" << (*it)->getGlobalBounds().width << ";height=" << (*it)->getGlobalBounds().height << "]" << std::endl;
               }
           }
        }
    }
    if(DEBUG)
    {
        std::cout << "Pas de collision " << std::endl;
    }
}

/**
* \fn jump(sf::FloatRect box1)
*
* \brief Try if box1 can jump correctly by motion
*
* \param box1 : The AABB to test
* \return True if the movement of box1 by motion is correct. False otherwise
**/
bool Engine::isAbleToJump(sf::FloatRect box)
{
    return true;
}
