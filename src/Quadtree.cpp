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
* \fn add(sf::Sprite* obj)
*
* \brief Add a object to the Quadtree
*
* \param obj : Object to be add
* \return True if object as added. false otherwise
**/
bool Quadtree::add(sf::Sprite* obj)
{
    if (!Engine::collisionAABB(m_boundary,obj->getGlobalBounds()))
    {
        return false;
    }

    if (m_elements.size() < QUAD_NODE_CAPACITY)
    {
        m_elements.push_back(obj);
        return true;
    } else {
        subdivide();
        if(m_northWest->add(obj))
        {
            return true;
        } else if (m_northEast->add(obj))
        {
            return true;
        } else if (m_southWest->add(obj))
        {
            return true;
        } else if (m_southEast->add(obj))
        {
            return true;
        }
    }

    return false;
}

/**
*
* \fn del(sf::Vector2f pos)
*
* \brief Delete a object from Quadtree at position pos
*
* \param pos : The position of the object to be deleted
* \return void
**/
void Quadtree::del(sf::Vector2f pos)
{

}

/**
*
* \fn queryRange(sf::Sprite* obj)
*
* \brief Search and return the vector of element around obj
*
* \param obj : The object on which we want to make query
* \return vector of element around obj. Return NULL if obj is not in quadrant
**/
std::vector<sf::Sprite*> Quadtree::queryRange(sf::Sprite* obj)
{
    std::vector<sf::Sprite*> elements;
    if(!Engine::collisionAABB(m_boundary,obj))
    {
        return NULL;
    }

    for(int i = 0; i < m_elements.size(); i++)
    {
        if(Engine::collisionAABB(obj,m_elements[i]))
        {
            elements.push_back(m_elements[i]);
        }

        if(m_northWest == NULL)
        {
            return elements;
        }

        elements.merge(m_northWest->queryRange(obj));
        elements.merge(m_northEast->queryRange(obj));
        elements.merge(m_southWest->queryRange(obj));
        elements.merge(m_southEast->queryRange(obj));

        return elements;
    }
}

/**
*
* \fn subdivide()
*
* \brief Create 4 childs to divide this quadrant into 4 egal quadrants dimensions
*
* \param
* \return void
**/
void Quadtree::subdivide()
{

}
