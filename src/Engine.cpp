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
    return !((box2.left >= box1.left + box1.width) ||
        (box2.left  + box2.width <= box1.left) ||
        (box2.top >= box1.top + box1.height) ||
        (box2.top + box2.height <= box1.top));
}

/**
* \fn move(sf::FloatRect box1, sf::Vector2f motion)
*
* \brief Try if box1 can move correctly by motion
*
* \param box1 : The AABB to test, motion : Motion Vector, universe : Quadtree which represents world
* \return True if the movement of box1 by motion is correct. False otherwise
**/
bool Engine::move(sf::Sprite box1, sf::Vector2f motion, Quadtree* universe)
{// TODO
    if(DEBUG)
    {
        std::cout << "*-----------------*" << std::endl;
        std::cout << "*  ENGINE : MOVE  *" << std::endl;
        std::cout << "*-----------------*" << std::endl;
    }
    sf::Vector2f initPos = box1.getPosition();
    box1.setPosition(initPos+motion);
    // TODO : gerer la collision quand le char est entre 2-3-4 quad
    std::vector<sf::Sprite*>* listObject = universe->queryRange(box1.getPosition());
    if(listObject->size() > 0)
    {
        std::cout << "Il y a " << listObject->size() << " en possible collision" << std::endl;
        for(std::vector<sf::Sprite*>::iterator it = listObject->begin(); it != listObject->end(); it++)
        {
           if(collisionAABB((*it)->getGlobalBounds(),box1.getGlobalBounds()))
           {
               std::cout << "*-----------*" << std::endl;
               std::cout << "  COLLISION  " << std::endl;
               std::cout << "*-----------*" << std::endl;
               std::cout << "Char : [x=" << box1.getGlobalBounds().left << ";y=" << box1.getGlobalBounds().top << ";width=" << box1.getGlobalBounds().width << ";height=" << box1.getGlobalBounds().height <<  "]" << std::endl;
               std::cout << "Tile : [x=" << (*it)->getGlobalBounds().left << ";y=" << (*it)->getGlobalBounds().top << ";width=" << (*it)->getGlobalBounds().width << ";height=" << (*it)->getGlobalBounds().height << "]" << std::endl;
               return false;
           }
        }
    }
    std::cout << "Pas de collision " << std::endl;
    return true;

    /*
    box1.setPosition(box1.getPosition()+motion);
    std::vector<sf::Sprite*>* listObject = universe->queryRange(box1.getPosition());
    if(listObject->size() == 0)
    {
        return true;
    } else {
        return false;
    }
*/
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
