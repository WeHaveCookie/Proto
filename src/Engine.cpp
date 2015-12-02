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
*
* \fn collisionAABB(AABB box1, AABB box2)
*
* \brief Detect collission between box1 and box2
*
* \param box1 : The first AABB, box2 : The second AABB
* \return Return True if there is a collision between the 2 box. False otherwise
**/

bool Engine::collisionAABB(AABB box1, AABB box2)
{
    return (box2.x >= box1.x + box1.w) || (box2.x  + box2.w <= box1.w) || (box2.y >= box1.y + box1.h || box2.y + box2.h <= box1.y);
}
