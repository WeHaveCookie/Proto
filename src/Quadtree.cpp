#include "Quadtree.hpp"

Quadtree::Quadtree(float x, float y, float width, float height)
{
    m_boundary.setPosition(x,y);
    m_boundary.setSize(sf::Vector2f(width,height));
    m_boundary.setFillColor(sf::Color(0,0,0,0));
    m_boundary.setOutlineThickness(1.0f);
    m_boundary.setOutlineColor(sf::Color::Green);
    m_shape = sf::FloatRect(x,y,width,height);
    m_elements = std::vector<sf::Sprite*>();
    m_northWest = NULL;
    m_northEast = NULL;
    m_southWest = NULL;
    m_southEast = NULL;
    m_enable = true;
}

Quadtree::~Quadtree()
{
    if(!m_elements.empty()) {
        delete m_northWest;
        delete m_northEast;
        delete m_southWest;
        delete m_southEast;
    }
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
/*Quadtree::Quadtree(std::list<sf::Sprite*> obj)
{

}*/

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
    if(DEBUG)
    {
        //std::cout << "*--AJOUT--*" << std::endl;
        //std::cout << "Current quad : [x=" << m_shape.top << ";y=" << m_shape.left << ";width=" << m_shape.width << ";height=" << m_shape.height << "]" << std::endl;
        //std::cout << "Ajout : [x=" << obj->getGlobalBounds().top << ";y=" << obj->getGlobalBounds().left << ";width=" << obj->getGlobalBounds().width << ";height=" << obj->getGlobalBounds().height << "]" << std::endl;
    }
    if (!m_shape.intersects(obj->getGlobalBounds()))
    {
        if(DEBUG)
        {
            //std::cout << "l'elem n'est pas dans le quad" << std::endl;
        }
        return false;
    } else
    {
        if (m_elements.size() < QUAD_NODE_CAPACITY && m_enable)
        {
            if(DEBUG)
            {
                std::cout << "*--AJOUT--*" << std::endl;
                std::cout << "Ajout : [x=" << obj->getGlobalBounds().top << ";y=" << obj->getGlobalBounds().left << ";width=" << obj->getGlobalBounds().width << ";height=" << obj->getGlobalBounds().height << "]" << std::endl;
                std::cout << "dans le quad : [x=" << m_shape.top << ";y=" << m_shape.left << ";width=" << m_shape.width << ";height=" << m_shape.height << ":TAILLE=" << m_elements.size() << "]" << std::endl;
                std::cout << "*---FIN---*" << std::endl;
            }
            m_elements.push_back(obj);
            return true;
        } else
        {
            if(m_elements.size() >= QUAD_NODE_CAPACITY && m_enable)
            {
                subdivide();
            }

            if(m_northWest->add(obj))
            {
                return true;
            }
            if (m_northEast->add(obj))
            {
                return true;
            }
            if (m_southWest->add(obj))
            {
                return true;
            }
            if (m_southEast->add(obj))
            {
                return true;
            }
        }

        return false;
    }
}

/**
*
* \fn del(sf::Vector2f pos)
*
* \brief Delete a object from Quadtree at position pos
*
* \param pos : The position of the object to be deleted
* \return the deleted object
**/
sf::Sprite* Quadtree::del(sf::Vector2f pos)
{
    sf::Sprite* delObject = NULL;
    if(!m_shape.intersects(sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT))) {
        return delObject;
    }

    if(m_elements.empty())
    {
        if(m_northWest->getShape().intersects(sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT)))
        {
            return m_northWest->del(pos);
        } else if (m_northEast->getShape().intersects(sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT)))
        {
            return m_northEast->del(pos);
        } else if (m_southWest->getShape().intersects(sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT)))
        {
            return m_southWest->del(pos);
        } else if (m_southEast->getShape().intersects(sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT)))
        {
            return m_southEast->del(pos);
        }
    } else
    {
        for(std::vector<sf::Sprite*>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
        {
            if((*it)->getGlobalBounds().intersects(sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT)))
            {
                delObject = *it;
                m_elements.erase(it);
                return delObject;
            }
        }
    }
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
    if(!m_shape.intersects(obj->getGlobalBounds()))
    {
        return elements;
    }

    for(std::vector<sf::Sprite*>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
    {
        if(obj->getGlobalBounds().intersects((*it)->getGlobalBounds()))
        {
            elements.push_back(*it);
        }

        if(m_northWest == NULL)
        {
            return elements;
        }

        std::vector<sf::Sprite*> query = m_northWest->queryRange(obj);
        elements.insert(elements.end(),query.begin(),query.end());
        query = m_northEast->queryRange(obj);
        elements.insert(elements.end(),query.begin(),query.end());
        query = m_southWest->queryRange(obj);
        elements.insert(elements.end(),query.begin(),query.end());
        query = m_southEast->queryRange(obj);
        elements.insert(elements.end(),query.begin(),query.end());

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
    if(DEBUG)
    {
        std::cout << "*-------------------------*" << std::endl;
        std::cout << "*On subdivise le quad en 4*" << std::endl;
        std::cout << "*-------------------------*" << std::endl;
    }
    m_northWest = new Quadtree(m_shape.left, m_shape.top, m_shape.width/2.0f, m_shape.height/2.0f);
    m_northEast = new Quadtree(m_shape.left+(m_shape.width/2.0f), m_shape.top, m_shape.width/2.0f, m_shape.height/2.0f);
    m_southWest = new Quadtree(m_shape.left, m_shape.top+(m_shape.height/2.0f), m_shape.width/2.0f, m_shape.height/2.0f);
    m_southEast = new Quadtree(m_shape.left+(m_shape.width/2.0f), m_shape.top+(m_shape.height/2.0f), m_shape.width/2.0f, m_shape.height/2.0f);
    if(!m_elements.empty())
    {
        if(DEBUG)
        {
            //std::cout << "Le quad maitre à des elements" << std::endl;
        }
        for(std::vector<sf::Sprite*>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
        {
            m_northWest->add(*it);
            m_northEast->add(*it);
            m_southWest->add(*it);
            m_southEast->add(*it);
        }
        m_elements.clear();
        if(DEBUG)
        {
            std::cout << "*-------------------------*" << std::endl;
            std::cout << "*--Fin de la subdivision--*" << std::endl;
            std::cout << "*-------------------------*" << std::endl;
        }
    }
    m_enable = false;
}

/**
*
* \fn clear()
*
* \brief Function to clear the quadtree
*
* \param
* \return void
**/
void Quadtree::clear()
{
    if(m_elements.empty()) {
        m_northWest->clear();
        m_northEast->clear();
        m_southWest->clear();
        m_southEast->clear();
    } else {
        m_elements.clear();
    }
}

/**
*
* \fn draw(sf::RenderWindow* window)
*
* \brief Draw the quadtree on window
*
* \param window : Window where draw the quadtree
* \return void
**/
void Quadtree::draw(sf::RenderWindow* window)
{
    window->draw(m_boundary);
    if(m_elements.empty() && m_northWest != NULL && m_northEast != NULL && m_southWest != NULL && m_southEast != NULL)
    {
        m_northWest->draw(window);
        m_northEast->draw(window);
        m_southWest->draw(window);
        m_southEast->draw(window);
    } else
    {
        for(std::vector<sf::Sprite*>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
        {
            window->draw(**it);
        }
    }
}


