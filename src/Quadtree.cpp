#include "Quadtree.hpp"

Quadtree::Quadtree(float x, float y, float width, float height)
{
    m_boundary.setPosition(x,y);
    m_boundary.setSize(sf::Vector2f(width,height));
    m_boundary.setFillColor(sf::Color(0,0,0,0));
    m_boundary.setOutlineThickness(1.0f);
    m_boundary.setOutlineColor(sf::Color::Green);
    m_shape = sf::FloatRect(x,y,width,height);
    m_elements = new std::vector<sf::Sprite*>;
    m_elements->reserve(sizeof(std::vector<sf::Sprite*>)*QUAD_NODE_CAPACITY);
    m_northWest = NULL;
    m_northEast = NULL;
    m_southWest = NULL;
    m_southEast = NULL;
    m_enable = true;
    m_displayTile = true;
}

Quadtree::~Quadtree()
{
    if(!m_enable) {
        delete m_northWest;
        delete m_northEast;
        delete m_southWest;
        delete m_southEast;
    }
    delete m_elements;
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
    if (!m_shape.intersects(obj->getGlobalBounds()))
    {
        if(DEBUG)
        {
            std::cout << "l'elem n'est pas dans le quad" << std::endl;
        }
        return false;
    } else
    {
        if (m_elements->size() < QUAD_NODE_CAPACITY && m_enable)
        {
            if(DEBUG)
            {
                std::cout << "*--AJOUT--*" << std::endl;
                std::cout << "Ajout : [x=" << obj->getGlobalBounds().left << ";y=" << obj->getGlobalBounds().top << ";width=" << obj->getGlobalBounds().width << ";height=" << obj->getGlobalBounds().height << "]" << std::endl;
                std::cout << "dans le quad : [x=" << m_shape.left << ";y=" << m_shape.top << ";width=" << m_shape.width << ";height=" << m_shape.height << ":TAILLE=" << m_elements->size() << "]" << std::endl;
                std::cout << "*---FIN---*" << std::endl;
            }
            m_elements->push_back(obj);
            return true;
        } else
        {
            if(m_elements->size() >= QUAD_NODE_CAPACITY && m_enable)
            {
                subdivide();
            }

            sf::IntRect textRect = obj->getTextureRect();
            sf::FloatRect bound = obj->getGlobalBounds();

            if(m_northWest->getShape().intersects(obj->getGlobalBounds()))
            {
                // On verifie si le tile est entre les quadrants NW et SW
                if(m_southWest->getShape().intersects(obj->getGlobalBounds()))
                {
                    // On verifie si le tile est entre tout les quadrants
                    if(m_southEast->getShape().intersects(obj->getGlobalBounds()) && m_northEast->getShape().intersects(obj->getGlobalBounds()))
                    {
                        /** Il faut couper le tile en 4 et l'ajouter dans les 4 quadrants **/
                        if(DEBUG)
                        {
                            std::cout << "Tile intersect NW - NE - SW - SE"<< std::endl;
                        }
                        sf::Sprite* spriteNW = new sf::Sprite;
                        sf::Sprite* spriteNE = new sf::Sprite;
                        sf::Sprite* spriteSW = new sf::Sprite;
                        sf::Sprite* spriteSE = new sf::Sprite;
                        spriteNW->setTexture(*obj->getTexture());
                        spriteNE->setTexture(*obj->getTexture());
                        spriteSW->setTexture(*obj->getTexture());
                        spriteSE->setTexture(*obj->getTexture());

                        // x = x
                        // y = y
                        // w = NW.w-x
                        // h = NW.h-y
                        spriteNW->setTextureRect(sf::IntRect(textRect.left,
                                                             textRect.top,
                                                             m_northWest->getShape().width - bound.left,
                                                             m_northWest->getShape().height - bound.top));
                        spriteNW->setPosition(sf::Vector2f(bound.left,bound.top));

                        // x = NE.x
                        // y = y
                        // w = w - (NW.w-x)
                        // h = NE.h - y
                        spriteNE->setTextureRect(sf::IntRect(textRect.left + (m_northWest->getShape().width - bound.left),
                                                             textRect.top,
                                                             textRect.width - (m_northWest->getShape().width - bound.left),
                                                             m_northEast->getShape().height - bound.top));
                        spriteNE->setPosition(sf::Vector2f(m_northEast->getShape().left,bound.top));

                        // x = x
                        // y = SW.y
                        // w = SW.w - x
                        // h = h - (NW.h - y)
                        spriteSW->setTextureRect(sf::IntRect(textRect.left,
                                                             textRect.top + (m_northWest->getShape().height - bound.top),
                                                             m_southWest->getShape().width - bound.left,
                                                             textRect.height - (m_northWest->getShape().height - bound.top)));
                        spriteSW->setPosition(sf::Vector2f(bound.left,m_southWest->getShape().top));

                        // x = SE.x
                        // y = SE.y
                        // w = w - (NW.w - x)
                        // h = h - (NW.h - y)
                        spriteSE->setTextureRect(sf::IntRect(textRect.left + (m_northWest->getShape().width - bound.left),
                                                             textRect.top + (m_northWest->getShape().height - bound.top),
                                                             textRect.width - (m_northWest->getShape().width - bound.left),
                                                             textRect.height - (m_northWest->getShape().height - bound.top)));
                        spriteSE->setPosition(sf::Vector2f(m_southEast->getShape().left,m_southEast->getShape().top));

                        // On ajoute les 4 sprites au quadrant correspondant
                        m_northWest->add(spriteNW);
                        m_northEast->add(spriteNE);
                        m_southWest->add(spriteSW);
                        m_southEast->add(spriteSE);
                    } else  // Il est dans le quadrant NW et SW
                    {
                        /** Il faut couper le tile en 2 et l'ajouter dans les quadrants NW et SW**/
                        if(DEBUG)
                        {
                            std::cout << "Tile intersect NW - SW"<< std::endl;
                        }
                        sf::Sprite* spriteNW = new sf::Sprite;
                        sf::Sprite* spriteSW = new sf::Sprite;
                        spriteNW->setTexture(*obj->getTexture());
                        spriteSW->setTexture(*obj->getTexture());

                        spriteNW->setTextureRect(sf::IntRect(textRect.left,
                                                             textRect.top,
                                                             textRect.width,
                                                             m_northWest->getShape().height - bound.top));
                        spriteNW->setPosition(sf::Vector2f(bound.left,bound.top));

                        spriteSW->setTextureRect(sf::IntRect(textRect.left,
                                                             textRect.top + (m_northWest->getShape().height - bound.top),
                                                             textRect.width,
                                                             textRect.height - (m_northWest->getShape().height - bound.top)));
                        spriteSW->setPosition(sf::Vector2f(bound.left,m_southWest->getShape().top));

                        m_northWest->add(spriteNW);
                        m_southWest->add(spriteSW);
                    } // On verifie si le tile est entre les quadrants NW et NE
                } else if (m_northEast->getShape().intersects(obj->getGlobalBounds()))
                {
                    /** Il faut couper le tile en 2 et l'ajouter dans les quadrants NW et NE**/
                    if(DEBUG)
                        {
                            std::cout << "Tile intersect NW - NE"<< std::endl;
                        }
                    sf::Sprite* spriteNW = new sf::Sprite;
                    sf::Sprite* spriteNE = new sf::Sprite;
                    spriteNW->setTexture(*obj->getTexture());
                    spriteNE->setTexture(*obj->getTexture());

                    spriteNW->setTextureRect(sf::IntRect(textRect.left,
                                                         textRect.top,
                                                         m_northWest->getShape().width - bound.left,
                                                         textRect.height));
                    spriteNW->setPosition(sf::Vector2f(sf::Vector2f(bound.left,bound.top)));


                    spriteNE->setTextureRect(sf::IntRect(textRect.left + (m_northWest->getShape().width - bound.left),
                                                         textRect.top,
                                                         textRect.width - (m_northWest->getShape().width - bound.left),
                                                         textRect.height));
                    spriteNE->setPosition(sf::Vector2f(m_northEast->getShape().left,bound.top));

                    m_northWest->add(spriteNW);
                    m_northEast->add(spriteNE);
                } else
                { // Il est uniquement dans le quadrant NW
                    m_northWest->add(obj);
                }
            } else if (m_northEast->getShape().intersects(obj->getGlobalBounds()))
            {
                // On verifie si le tile est entre les quadrants NE et SE
                if(m_southEast->getShape().intersects(obj->getGlobalBounds()))
                {
                    /** Il faut couper le tile en 2 et le rajouter dans les quadrants NE et SE**/
                    if(DEBUG)
                    {
                        std::cout << "Tile intersect NE - SE"<< std::endl;
                    }
                    sf::Sprite* spriteNE = new sf::Sprite;
                    sf::Sprite* spriteSE = new sf::Sprite;
                    spriteNE->setTexture(*obj->getTexture());
                    spriteSE->setTexture(*obj->getTexture());

                    spriteNE->setTextureRect(sf::IntRect(textRect.left,
                                                         textRect.top,
                                                         textRect.width,
                                                         m_northEast->getShape().height - bound.top));
                    spriteNE->setPosition(sf::Vector2f(bound.left,bound.top));


                    spriteSE->setTextureRect(sf::IntRect(textRect.left,
                                                         textRect.top + (m_northWest->getShape().height - bound.top),
                                                         textRect.width,
                                                         textRect.height - (m_northWest->getShape().height - bound.top)));
                    spriteSE->setPosition(sf::Vector2f(bound.left,m_southEast->getShape().top));

                    m_northEast->add(spriteNE);
                    m_southEast->add(spriteSE);

                } else // Il est uniquement dans le quadrant NE
                {
                    m_northEast->add(obj);
                }
            } else if (m_southWest->getShape().intersects(obj->getGlobalBounds()))
            {
                // On verifie si le tile est entre les quadrants SW et SE
                if(m_southEast->getShape().intersects(obj->getGlobalBounds()))
                {
                    /** Il faut couper le tile en 2 et le rajouter dans les quadrants SW et SE**/
                    if(DEBUG)
                    {
                        std::cout << "Tile intersect SW - SE"<< std::endl;
                    }
                    sf::Sprite* spriteSW = new sf::Sprite;
                    sf::Sprite* spriteSE = new sf::Sprite;
                    spriteSW->setTexture(*obj->getTexture());
                    spriteSE->setTexture(*obj->getTexture());

                    spriteSW->setTextureRect(sf::IntRect(textRect.left,
                                                         textRect.top,
                                                         m_southWest->getShape().width - bound.left,
                                                         textRect.height));
                    spriteSW->setPosition(sf::Vector2f(bound.left,bound.top));


                    spriteSE->setTextureRect(sf::IntRect(textRect.left + (m_northWest->getShape().width - bound.left),
                                                         textRect.top,
                                                         textRect.width - (m_northWest->getShape().width - bound.left),
                                                         textRect.height));
                    spriteSE->setPosition(sf::Vector2f(m_southEast->getShape().left,bound.top));

                    m_southWest->add(spriteSW);
                    m_southEast->add(spriteSE);
                } else // Il est uniquement dans le quadrant SW
                {
                    m_southWest->add(obj);
                }
            } else if (m_southEast->getShape().intersects(obj->getGlobalBounds()))
            {
                m_southEast->add(obj);
            }

            return true;
        }
        return false;
    }
}

/**
*
* \fn del(sf::FloatRect pos)
*
* \brief Delete a object from Quadtree at position pos
*
* \param pos : The position of the object to be deleted
* \return the deleted object
**/
sf::Sprite* Quadtree::del(sf::FloatRect pos)
{
    //sf::FloatRect posRect = sf::FloatRect(pos.x,pos.y,SPRITE_WIDTH,SPRITE_HEIGHT);
    sf::Sprite* delObject = NULL;
    if(!m_shape.intersects(pos)) {
        return delObject;
    }

    if(m_elements->empty() && !m_enable)
    {
        if(m_northWest->getShape().intersects(pos))
        {
            delObject = m_northWest->del(pos);
        } else if (m_northEast->getShape().intersects(pos))
        {
            delObject = m_northEast->del(pos);
        } else if (m_southWest->getShape().intersects(pos))
        {
            delObject = m_southWest->del(pos);
        } else if (m_southEast->getShape().intersects(pos))
        {
            delObject = m_southEast->del(pos);
        }
        if(DEBUG)
        {
            std::cout << "-- Nbr Elem : " << m_northWest->nbElement() + m_northEast->nbElement() + m_southWest->nbElement() + m_southEast->nbElement() << "--" << std::endl;
        }
        if((m_northWest->nbElement() + m_northEast->nbElement() + m_southWest->nbElement() + m_southEast->nbElement()) <= QUAD_NODE_CAPACITY)
        {
           merge();
        }
        return delObject;
    } else
    {
        for(std::vector<sf::Sprite*>::iterator it = m_elements->begin(); it != m_elements->end(); it++)
        {
            if((*it)->getGlobalBounds().intersects(pos))
            {
                delObject = *it;
                m_elements->erase(it);
                return delObject;
            }
        }
    }
    return delObject;
}

/**
*
* \fn queryRange(sf::FloatRect pos)
*
* \brief Search and return the vector of element around obj
*
* \param obj : The object on which we want to make query
* \return vector of element around obj. Return NULL if obj is not in quadrant
**/
std::vector<sf::Sprite*>* Quadtree::queryRange(sf::FloatRect pos)
{ // WARNING : La collision lorsque le char n'intersect pas le quadrant n'est pas géré
    if(DEBUG)
    {
        std::cout << "*--------------*" << std::endl;
        std::cout << "* START QUERY  *" << std::endl;
        std::cout << "*--------------*" << std::endl;
        std::cout << "Query at [x=" << pos.left << ";y=" << pos.top << ";width=" << pos.width << ";height=" << pos.height << "]" << std::endl;
        std::cout << "On shape [x=" << m_shape.left << ";y=" << m_shape.top << ";width=" << m_shape.width << ";height=" << m_shape.height << "]" << std::endl;
    }
    std::vector<sf::Sprite*>* answer = new std::vector<sf::Sprite*>;
    if(DEBUG)
    {
        std::cout << "answer create" << std::endl;
    }
    if(!m_shape.intersects(pos))
    {
        if(DEBUG)
        {
            std::cout << "*******************" << std::endl;
            std::cout << "*-----------------*" << std::endl;
            std::cout << "not in shape ! O.o" << std::endl;
            std::cout << "*-----------------*" << std::endl;
            std::cout << "*******************" << std::endl;
        }
        return answer;
    }
    if(m_enable)
    {
        answer = getElements();
        return answer;
    } else
    {
        if(DEBUG)
        {
            std::cout << "Le quad [x=" << m_shape.left << ";y=" << m_shape.top << ";width=" << m_shape.width << ":height=" << m_shape.height << "] !enable, on recherche dans les fils" << std::endl;
        }
        std::vector<sf::Sprite*>* tmp = new std::vector<sf::Sprite*>;
        if(m_northWest->getShape().intersects(pos))
        {
            tmp = m_northWest->queryRange(pos);
            if(tmp != NULL)
            {
                answer->insert(answer->end(),tmp->begin(),tmp->end());
            }

        }
        if (m_northEast->getShape().intersects(pos))
        {
            tmp = m_northEast->queryRange(sf::FloatRect(pos));
            if(tmp != NULL)
            {
                answer->insert(answer->end(),tmp->begin(),tmp->end());
            }

        }
        if (m_southWest->getShape().intersects(pos))
        {
            tmp = m_southWest->queryRange(sf::FloatRect(pos));
            if(tmp != NULL)
            {
                answer->insert(answer->end(),tmp->begin(),tmp->end());
            }

        }
        if (m_southEast->getShape().intersects(pos))
        {
            tmp = m_southEast->queryRange(sf::FloatRect(pos));
            if(tmp != NULL)
            {
                answer->insert(answer->end(),tmp->begin(),tmp->end());
            }
        }
        return answer;
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
    m_enable = false;
    if(!m_elements->empty())
    {
        if(DEBUG)
        {
            std::cout << "Le quad maitre à des elements" << std::endl;
        }
        for(std::vector<sf::Sprite*>::iterator it = m_elements->begin(); it != m_elements->end(); it++)
        {
            /*if(m_northWest->getShape().intersects((*it)->getGlobalBounds()))
            {
                m_northWest->add(*it);
            } else if (m_northEast->getShape().intersects((*it)->getGlobalBounds()))
            {
                m_northEast->add(*it);
            } else if (m_southWest->getShape().intersects((*it)->getGlobalBounds()))
            {
                m_southWest->add(*it);
            } else if (m_southEast->getShape().intersects((*it)->getGlobalBounds()))
            {
                m_southEast->add(*it);
            }*/
            add(*it);
        }
        m_elements->clear();
        if(DEBUG)
        {
            std::cout << "*-------------------------*" << std::endl;
            std::cout << "*--Fin de la subdivision--*" << std::endl;
            std::cout << "*-------------------------*" << std::endl;
        }
    }

}

/**
*
* \fn merge()
*
* \brief Merge the quadtree when Sum(child element) < QUAD_NODE_CAPACITY
*
* \param
* \return void
**/
void Quadtree::merge()
{
    if(DEBUG)
    {
        std::cout << "*---------*" << std::endl;
        std::cout << "*  MERGE  *" << std::endl;
        std::cout << "*---------*" << std::endl;
    }
    m_elements = new std::vector<sf::Sprite*>;
    m_elements->reserve(m_northWest->getElements()->size()+m_northEast->getElements()->size()+m_southWest->getElements()->size()+m_southEast->getElements()->size());
    m_elements->insert(m_elements->end(),m_northWest->getElements()->begin(),m_northWest->getElements()->end());
    m_elements->insert(m_elements->end(),m_northEast->getElements()->begin(),m_northEast->getElements()->end());
    m_elements->insert(m_elements->end(),m_southWest->getElements()->begin(),m_southWest->getElements()->end());
    m_elements->insert(m_elements->end(),m_southEast->getElements()->begin(),m_southEast->getElements()->end());
    clear();
    if(DEBUG)
    {
        std::cout << "*----------------*" << std::endl;
        std::cout << "*  END OF MERGE  *" << std::endl;
        std::cout << "*----------------*" << std::endl;
    }
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
    if(DEBUG)
    {
        std::cout << "*----------------*" << std::endl;
        std::cout << "* DEBUT DU CLEAR *" << std::endl;
        std::cout << "*----------------*" << std::endl;
    }
    if(!m_enable) {
        m_northWest->clear();
        m_northEast->clear();
        m_southWest->clear();
        m_southEast->clear();
        if(DEBUG)
        {
            std::cout << "*--ON DELETE--*" << std::endl;
        }
        delete m_northWest;
        delete m_northEast;
        delete m_southWest;
        delete m_southEast;
        m_northWest = NULL;
        m_northEast = NULL;
        m_southWest = NULL;
        m_southEast = NULL;
        m_enable = true;
    } else {
        if(DEBUG)
        {
            std::cout << "*--CLEAR--*" << std::endl;
        }
        m_elements->clear();
    }
    if(DEBUG)
    {
        std::cout << "*----------------*" << std::endl;
        std::cout << "*  FIN DU CLEAR  *" << std::endl;
        std::cout << "*----------------*" << std::endl << std::endl;
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
    if(m_elements->empty() && m_northWest != NULL && m_northEast != NULL && m_southWest != NULL && m_southEast != NULL)
    {
        m_northWest->draw(window);
        m_northEast->draw(window);
        m_southWest->draw(window);
        m_southEast->draw(window);
    } else
    {
        if(m_displayTile)
        {
            for(std::vector<sf::Sprite*>::iterator it = m_elements->begin(); it != m_elements->end(); it++)
            {
                window->draw(**it);
            }
        }
    }
}

/**
*
* \fn void displayCase(bool b)
*
* \brief Set if tree display tile or not
*
* \param b : True for display tile, false otherwise
* \return void
**/
void Quadtree::displayTile(bool b)
{
    m_displayTile = b;
    if(!m_enable) {
        m_northWest->displayTile(b);
        m_northEast->displayTile(b);
        m_southWest->displayTile(b);
        m_southEast->displayTile(b);
    }
}

int Quadtree::nbElement()
{
    if(m_enable)
    {
        return m_elements->size();
    } else
    {
        return m_northWest->nbElement() + m_northEast->nbElement() + m_southWest->nbElement() + m_southEast->nbElement();
    }

}
