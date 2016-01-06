#include "Quadtree.hpp"

/**
*
* \fn Quadtree(float x, float y, float width, float height)
*
* \brief Basic constructor of Quadtree
*
* \param x & y : position of Quatree, width : width of Quatree, height : height of Quatree
* \return
**/
Quadtree::Quadtree(float x, float y, float width, float height)
{
    m_boundary.setPosition(x,y);
    m_boundary.setSize(sf::Vector2f(width,height));
    m_boundary.setFillColor(sf::Color(0,0,0,0));
    m_boundary.setOutlineThickness(1.0f);
    m_boundary.setOutlineColor(sf::Color::Green);
    m_shape = sf::FloatRect(x,y,width,height);
    m_northWest = NULL;
    m_northEast = NULL;
    m_southWest = NULL;
    m_southEast = NULL;
    m_enable = true;
    m_displayTile = true;
    if(DEBUG)
    {
        std::cout << "Storage capacity : " << m_elements.capacity() << std::endl;
    }
}

/**
*
* \fn ~Quadtree()
*
* \brief Destructor of quadtree
*
* \param
* \return
**/
Quadtree::~Quadtree()
{
    if(DEBUG)
    {
        std::cout << "~Quadtree" << std::endl;
    }
    if(!m_enable) {
        delete m_northWest;
        delete m_northEast;
        delete m_southWest;
        delete m_southEast;
    }
    m_elements.clear();
    m_splitedElements.clear();
}


/**
*
* \fn Quadtree(float x, float y, float width, float height,  std::vector<std::shared_ptr<sf::Sprite>> obj)
*
* \brief Built a Quadtree with a existing vector of object
*
* \param obj : vector of Object
* \return Built the Quadtree which matching to object
**/
Quadtree::Quadtree(float x, float y, float width, float height,  std::vector<std::shared_ptr<sf::Sprite>> obj)
{
    Quadtree(x,y,width,height);
    for(std::vector<std::shared_ptr<sf::Sprite>>::iterator it = obj.begin(); it != obj.end(); it++)
    {
        add(*(it)->get());
    }
}

/**
*
* \fn add(sf::Sprite obj)
*
* \brief Add a object to the Quadtree
*
* \param obj : Object to be add
* \return True if object as added. false otherwise
**/
bool Quadtree::add(sf::Sprite obj)
{
    sf::FloatRect bound = obj.getGlobalBounds();
    if (!m_shape.intersects(bound))
    {
        if(DEBUG)
        {
            std::cout << "l'elem n'est pas dans le quad" << std::endl;
        }
        return false;
    } else
    {
        if (m_elements.size() < QUAD_NODE_CAPACITY && m_enable)
        {
            if(DEBUG)
            {
                std::cout << "*--AJOUT--*" << std::endl;
                std::cout << "Ajout : [x=" << bound.left << ";y=" << bound.top << ";width=" << bound.width << ";height=" << bound.height << "]" << std::endl;
                std::cout << "dans le quad : [x=" << m_shape.left << ";y=" << m_shape.top << ";width=" << m_shape.width << ";height=" << m_shape.height << ":TAILLE=" << m_elements.size() << "]" << std::endl;
                std::cout << "*---FIN---*" << std::endl;
            }
            m_elements.push_back(std::make_shared<sf::Sprite>(obj));
            if(DEBUG)
            {
                std::cout << "Storage capacity : " << m_elements.capacity() << std::endl;
            }
            return true;
        } else
        {
            if(m_elements.size() >= QUAD_NODE_CAPACITY && m_enable)
            {
                subdivide();
            }

            // On prepare la fragmentation du sprite
            sf::IntRect tRect = obj.getTextureRect();
            if(DEBUG)
            {
                std::cout << "*--------*" << std::endl;
                std::cout << "*--FRAG--*" << std::endl;
                std::cout << "*--------*" << std::endl;
                std::cout << "tRect [x=" << tRect.left << ";y=" << tRect.top << ";w=" << tRect.width << ";h=" << tRect.height <<  "]" <<std::endl;
            }
            SplitedSprite spl = SplitedSprite();
            spl.origin = std::make_shared<sf::Sprite>(obj);
            spl.NW = NULL;
            spl.NE = NULL;
            spl.SW = NULL;
            spl.SE = NULL;
            sf::IntRect tSpriteNW;
            sf::IntRect tSpriteNE;
            sf::IntRect tSpriteSW;
            sf::IntRect tSpriteSE;
            sf::Vector2f pSpriteNW;
            sf::Vector2f pSpriteNE;
            sf::Vector2f pSpriteSW;
            sf::Vector2f pSpriteSE;
            sf::FloatRect shapeNW = m_northWest->getShape();
            sf::FloatRect shapeNE = m_northEast->getShape();
            sf::FloatRect shapeSW = m_southWest->getShape();
            sf::FloatRect shapeSE = m_southEast->getShape();
            std::shared_ptr<sf::Sprite> spriteNW = std::make_shared<sf::Sprite>();
            std::shared_ptr<sf::Sprite> spriteNE = std::make_shared<sf::Sprite>();
            std::shared_ptr<sf::Sprite> spriteSW = std::make_shared<sf::Sprite>();
            std::shared_ptr<sf::Sprite> spriteSE = std::make_shared<sf::Sprite>();
            spriteNW->setTexture(*obj.getTexture());
            spriteNE->setTexture(*obj.getTexture());
            spriteSW->setTexture(*obj.getTexture());
            spriteSE->setTexture(*obj.getTexture());

            /////////////
            //SPRITE NW//
            /////////////
            //////////////////////////////////////////////////////////////////////////////
            tSpriteNW.left = tRect.left;
            tSpriteNW.top = tRect.top;
            pSpriteNW.x = bound.left;
            pSpriteNW.y = bound.top;
            spriteNW->setTextureRect(tSpriteNW);
            spriteNW->setPosition(pSpriteNW);
            //////////////////////////////////////////////////////////////////////////////

            /////////////
            //SPRITE NE//
            /////////////
            //////////////////////////////////////////////////////////////////////////////
            tSpriteNE.top = tRect.top;
            pSpriteNE.y = bound.top;
            spriteNE->setTextureRect(tSpriteNE);
            spriteNE->setPosition(pSpriteNE);
            //////////////////////////////////////////////////////////////////////////////

            /////////////
            //SPRITE SW//
            /////////////
            //////////////////////////////////////////////////////////////////////////////
            tSpriteSW.left = tRect.left;
            pSpriteSW.x = bound.left;
            spriteSW->setTextureRect(tSpriteSW);
            spriteSW->setPosition(pSpriteSW);
            //////////////////////////////////////////////////////////////////////////////

            /////////////
            //SPRITE SE//
            /////////////
            //////////////////////////////////////////////////////////////////////////////
            spriteSE->setTextureRect(tSpriteSE);
            spriteSE->setPosition(pSpriteSE);
            //////////////////////////////////////////////////////////////////////////////

            if(shapeNW.intersects(bound))
            {
                // On verifie si le tile est entre les quadrants NW et SW
                if(shapeSW.intersects(bound))
                {
                    // On verifie si le tile est entre tout les quadrants
                    if(shapeSE.intersects(bound) && shapeNE.intersects(bound))
                    {
                        /** Il faut couper le tile en 4 et l'ajouter dans les 4 quadrants **/
                        if(DEBUG)
                        {
                            std::cout << "Tile intersect NW - NE - SW - SE"<< std::endl;
                            std::cout << "ShapeNW = [x=" << shapeNW.left << ";y=" << shapeNW.top << ";w=" << shapeNW.width << ";h=" << shapeNW.height << "]" << std::endl;
                            std::cout << "ShapeNE = [x=" << shapeNE.left << ";y=" << shapeNE.top << ";w=" << shapeNE.width << ";h=" << shapeNE.height << "]" << std::endl;
                            std::cout << "ShapeSW = [x=" << shapeSW.left << ";y=" << shapeSW.top << ";w=" << shapeSW.width << ";h=" << shapeSW.height << "]" << std::endl;
                            std::cout << "ShapeSE = [x=" << shapeSE.left << ";y=" << shapeSE.top << ";w=" << shapeSE.width << ";h=" << shapeSE.height << "]" << std::endl;
                        }
                        /////////////
                        //SPRITE NW//
                        /////////////
                        //////////////////////////////////////////////////////////////////////////////
                        tSpriteNW.width = shapeNE.left - bound.left;
                        tSpriteNW.height = shapeSW.top - bound.top;
                        spriteNW->setTextureRect(tSpriteNW);
                        spriteNW->setPosition(pSpriteNW);
                        //////////////////////////////////////////////////////////////////////////////
                        if(DEBUG)
                        {
                            std::cout << "spriteNW [tx=" << tSpriteNW.left << ";ty=" << tSpriteNW.top << ";w=" << tSpriteNW.width << ";h=" << tSpriteNW.height << "] [x=" << pSpriteNW.x << ";y=" << pSpriteNW.y << "]" << std::endl;
                        }
                        /////////////
                        //SPRITE NE//
                        /////////////
                        //////////////////////////////////////////////////////////////////////////////
                        tSpriteNE.left = tRect.left + tSpriteNW.width;
                        tSpriteNE.width = bound.width - tSpriteNW.width;
                        tSpriteNE.height = shapeSE.top - bound.top;
                        pSpriteNE.x = shapeNE.left;
                        spriteNE->setTextureRect(tSpriteNE);
                        spriteNE->setPosition(pSpriteNE);
                        //////////////////////////////////////////////////////////////////////////////
                        if(DEBUG)
                        {
                            std::cout << "spriteNE [tx=" << tSpriteNE.left << ";ty=" << tSpriteNE.top << ";w=" << tSpriteNE.width << ";h=" << tSpriteNE.height << "] [x=" << pSpriteNE.x << ";y=" << pSpriteNE.y << "]" << std::endl;
                        }
                        /////////////
                        //SPRITE SW//
                        /////////////
                        //////////////////////////////////////////////////////////////////////////////
                        tSpriteSW.top = tRect.top + tSpriteNW.height;
                        tSpriteSW.width = shapeSE.left - bound.left;
                        tSpriteSW.height = bound.height - tSpriteNW.height;
                        pSpriteSW.y = shapeSW.top;
                        spriteSW->setTextureRect(tSpriteSW);
                        spriteSW->setPosition(pSpriteSW);
                        //////////////////////////////////////////////////////////////////////////////
                        if(DEBUG)
                        {
                            std::cout << "spriteSW [tx=" << tSpriteSW.left << ";ty=" << tSpriteSW.top << ";w=" << tSpriteSW.width << ";h=" << tSpriteSW.height << "] [x=" << pSpriteSW.x << ";y=" << pSpriteSW.y << "]" << std::endl;
                        }
                        /////////////
                        //SPRITE SE//
                        /////////////
                        //////////////////////////////////////////////////////////////////////////////
                        tSpriteSE.left = tRect.left + tSpriteNW.width;
                        tSpriteSE.top = tRect.top + tSpriteNW.height;
                        tSpriteSE.width = bound.width - tSpriteNW.width;
                        tSpriteSE.height = bound.height - tSpriteNW.height;
                        pSpriteSE.x = shapeSE.left;
                        pSpriteSE.y = shapeSE.top;
                        spriteSE->setTextureRect(tSpriteSE);
                        spriteSE->setPosition(pSpriteSE);
                        //////////////////////////////////////////////////////////////////////////////
                        if(DEBUG)
                        {
                            std::cout << "spriteSE [tx=" << tSpriteSE.left << ";ty=" << tSpriteSE.top << ";w=" << tSpriteSE.width << ";h=" << tSpriteSE.height << "] [x=" << pSpriteSE.x << ";y=" << pSpriteSE.y << "]" << std::endl;
                        }

                        // On ajoute les 4 sprites splitté au quadrant père
                        if(DEBUGLOCAL)
                        {
                            std::cout << "Ajout dans tout les quadrant" << std::endl;
                        }
                        spl.NW = spriteNW;
                        spl.NE = spriteNE;
                        spl.SW = spriteSW;
                        spl.SE = spriteSE;
                        m_splitedElements.push_back(std::make_shared<SplitedSprite>(spl));
                        // On ajoute les 4 sprites au quadrant correspondant
                        m_northWest->add(*spriteNW);
                        m_northEast->add(*spriteNE);
                        m_southWest->add(*spriteSW);
                        m_southEast->add(*spriteSE);
                    } else  // Il est dans le quadrant NW et SW
                    {
                        /** Il faut couper le tile en 2 et l'ajouter dans les quadrants NW et SW**/
                        if(DEBUG)
                        {
                            std::cout << "Tile intersect NW - SW"<< std::endl;
                            std::cout << "ShapeNW = [x=" << shapeNW.left << ";y=" << shapeNW.top << ";w=" << shapeNW.width << ";h=" << shapeNW.height << "]" << std::endl;
                            std::cout << "ShapeSW = [x=" << shapeSW.left << ";y=" << shapeSW.top << ";w=" << shapeSW.width << ";h=" << shapeSW.height << "]" << std::endl;
                        }
                        /////////////
                        //SPRITE NW//
                        /////////////
                        //////////////////////////////////////////////////////////////////////////////
                        tSpriteNW.width = bound.width;
                        tSpriteNW.height = shapeSW.top - bound.top;
                        spriteNW->setTextureRect(tSpriteNW);
                        spriteNW->setPosition(pSpriteNW);
                        //////////////////////////////////////////////////////////////////////////////
                        if(DEBUG)
                        {
                            std::cout << "spriteNW [tx=" << tSpriteNW.left << ";ty=" << tSpriteNW.top << ";w=" << tSpriteNW.width << ";h=" << tSpriteNW.height << "] [x=" << pSpriteNW.x << ";y=" << pSpriteNW.y << "]" << std::endl;
                        }
                        /////////////
                        //SPRITE SW//
                        /////////////
                        //////////////////////////////////////////////////////////////////////////////
                        tSpriteSW.top = tRect.top + tSpriteNW.height;
                        tSpriteSW.width = bound.width;
                        tSpriteSW.height = bound.height - tSpriteNW.height;
                        pSpriteSW.y = shapeSW.top;
                        spriteSW->setTextureRect(tSpriteSW);
                        spriteSW->setPosition(pSpriteSW);
                        //////////////////////////////////////////////////////////////////////////////
                        if(DEBUG)
                        {
                            std::cout << "spriteSW [tx=" << tSpriteSW.left << ";ty=" << tSpriteSW.top << ";w=" << tSpriteSW.width << ";h=" << tSpriteSW.height << "] [x=" << pSpriteSW.x << ";y=" << pSpriteSW.y << "]" << std::endl;
                        }
                        // On ajoute les 2 sprites splitté au quadrant père
                        if(DEBUG)
                        {
                            std::cout << "Ajout dans NW - SW" << std::endl;
                        }
                        spl.NW = spriteNW;
                        spl.SW = spriteSW;
                        m_splitedElements.push_back(std::make_shared<SplitedSprite>(spl));
                        m_northWest->add(*spriteNW);
                        m_southWest->add(*spriteSW);
                    } // On verifie si le tile est entre les quadrants NW et NE
                } else if (shapeNE.intersects(bound))
                {
                    /** Il faut couper le tile en 2 et l'ajouter dans les quadrants NW et NE**/
                    if(DEBUG)
                    {
                        std::cout << "Tile intersect NW - NE"<< std::endl;
                        std::cout << "ShapeNW = [x=" << shapeNW.left << ";y=" << shapeNW.top << ";w=" << shapeNW.width << ";h=" << shapeNW.height << "]" << std::endl;
                        std::cout << "ShapeNE = [x=" << shapeNE.left << ";y=" << shapeNE.top << ";w=" << shapeNE.width << ";h=" << shapeNE.height << "]" << std::endl;
                    }
                    /////////////
                    //SPRITE NW//
                    /////////////
                    //////////////////////////////////////////////////////////////////////////////
                    tSpriteNW.width = shapeNE.left - bound.left;
                    tSpriteNW.height = bound.height;
                    spriteNW->setTextureRect(tSpriteNW);
                    spriteNW->setPosition(pSpriteNW);
                    //////////////////////////////////////////////////////////////////////////////
                    if(DEBUG)
                    {
                        std::cout << "spriteNW [tx=" << tSpriteNW.left << ";ty=" << tSpriteNW.top << ";w=" << tSpriteNW.width << ";h=" << tSpriteNW.height << "] [x=" << pSpriteNW.x << ";y=" << pSpriteNW.y << "]" << std::endl;
                    }
                    /////////////
                    //SPRITE NE//
                    /////////////
                    //////////////////////////////////////////////////////////////////////////////
                    tSpriteNE.left = tRect.left + tSpriteNW.width;
                    tSpriteNE.width = bound.width - tSpriteNW.width;
                    tSpriteNE.height = bound.height;
                    pSpriteNE.x = shapeNE.left;
                    spriteNE->setTextureRect(tSpriteNE);
                    spriteNE->setPosition(pSpriteNE);
                    //////////////////////////////////////////////////////////////////////////////
                    if(DEBUG)
                    {
                        std::cout << "spriteNE [tx=" << tSpriteNE.left << ";ty=" << tSpriteNE.top << ";w=" << tSpriteNE.width << ";h=" << tSpriteNE.height << "] [x=" << pSpriteNE.x << ";y=" << pSpriteNE.y << "]" << std::endl;
                    }

                    // On ajoute les 2 sprites splitté au quadrant père
                    if(DEBUG)
                    {
                        std::cout << "Ajout dans NW - NE" << std::endl;
                    }
                    spl.NW = spriteNW;
                    spl.NE = spriteNE;
                    m_splitedElements.push_back(std::make_shared<SplitedSprite>(spl));
                    m_northWest->add(*spriteNW);
                    m_northEast->add(*spriteNE);
                } else
                { // Il est uniquement dans le quadrant NW
                    if(DEBUG)
                    {
                        std::cout << "Ajout dans NW" << std::endl;
                    }
                    m_northWest->add(obj);
                }
            } else if (shapeNE.intersects(bound))
            {
                // On verifie si le tile est entre les quadrants NE et SE
                if(shapeSE.intersects(bound))
                {
                    /** Il faut couper le tile en 2 et le rajouter dans les quadrants NE et SE**/
                    if(DEBUG)
                    {
                        std::cout << "Tile intersect NE - SE"<< std::endl;
                        std::cout << "ShapeNE = [x=" << shapeNE.left << ";y=" << shapeNE.top << ";w=" << shapeNE.width << ";h=" << shapeNE.height << "]" << std::endl;
                        std::cout << "ShapeSE = [x=" << shapeSE.left << ";y=" << shapeSE.top << ";w=" << shapeSE.width << ";h=" << shapeSE.height << "]" << std::endl;
                    }
                    /////////////
                    //SPRITE NE//
                    /////////////
                    //////////////////////////////////////////////////////////////////////////////
                    tSpriteNE.left = tRect.left;
                    tSpriteNE.width = bound.width;
                    tSpriteNE.height = shapeSE.top - bound.top;
                    pSpriteNE.x = bound.left;
                    spriteNE->setTextureRect(tSpriteNE);
                    spriteNE->setPosition(pSpriteNE);
                    //////////////////////////////////////////////////////////////////////////////
                    if(DEBUG)
                    {
                        std::cout << "spriteNE [tx=" << tSpriteNE.left << ";ty=" << tSpriteNE.top << ";w=" << tSpriteNE.width << ";h=" << tSpriteNE.height << "] [x=" << pSpriteNE.x << ";y=" << pSpriteNE.y << "]" << std::endl;
                    }
                    /////////////
                    //SPRITE SE//
                    /////////////
                    //////////////////////////////////////////////////////////////////////////////
                    tSpriteSE.left = tRect.left;
                    tSpriteSE.top = tRect.top + tSpriteNE.height;
                    tSpriteSE.width = bound.width;
                    tSpriteSE.height = bound.height - tSpriteNE.height;
                    pSpriteSE.x = bound.left;
                    pSpriteSE.y = shapeSE.top;
                    spriteSE->setTextureRect(tSpriteSE);
                    spriteSE->setPosition(pSpriteSE);
                    //////////////////////////////////////////////////////////////////////////////
                    if(DEBUG)
                    {
                        std::cout << "spriteSE [tx=" << tSpriteSE.left << ";ty=" << tSpriteSE.top << ";w=" << tSpriteSE.width << ";h=" << tSpriteSE.height << "] [x=" << pSpriteSE.x << ";y=" << pSpriteSE.y << "]" << std::endl;
                    }
                    // On ajoute les 2 sprites splitté au quadrant père
                    if(DEBUGLOCAL)
                    {
                        std::cout << "Ajout dans NE - SE" << std::endl;
                    }
                    spl.NE = spriteNE;
                    spl.SE = spriteSE;
                    m_splitedElements.push_back(std::make_shared<SplitedSprite>(spl));
                    m_northEast->add(*spriteNE);
                    m_southEast->add(*spriteSE);

                } else // Il est uniquement dans le quadrant NE
                {
                    if(DEBUG)
                    {
                        std::cout << "Ajout dans NE" << std::endl;
                    }
                    m_northEast->add(obj);
                }
            } else if (shapeSW.intersects(bound))
            {
                // On verifie si le tile est entre les quadrants SW et SE
                if(shapeSE.intersects(bound))
                {
                    /** Il faut couper le tile en 2 et le rajouter dans les quadrants SW et SE**/
                    if(DEBUG)
                    {
                        std::cout << "Tile intersect SW - SE"<< std::endl;
                        std::cout << "ShapeSE = [x=" << shapeSE.left << ";y=" << shapeSE.top << ";w=" << shapeSE.width << ";h=" << shapeSE.height << "]" << std::endl;
                        std::cout << "ShapeSW = [x=" << shapeSW.left << ";y=" << shapeSW.top << ";w=" << shapeSW.width << ";h=" << shapeSW.height << "]" << std::endl;
                    }
                    /////////////
                    //SPRITE SW//
                    /////////////
                    //////////////////////////////////////////////////////////////////////////////
                    tSpriteSW.top = tRect.top;
                    tSpriteSW.width = shapeSE.left - bound.left;
                    tSpriteSW.height = bound.height;
                    pSpriteSW.y = bound.top;
                    spriteSW->setTextureRect(tSpriteSW);
                    spriteSW->setPosition(pSpriteSW);
                    //////////////////////////////////////////////////////////////////////////////
                    if(DEBUG)
                    {
                        std::cout << "spriteSW [tx=" << tSpriteSW.left << ";ty=" << tSpriteSW.top << ";w=" << tSpriteSW.width << ";h=" << tSpriteSW.height << "] [x=" << pSpriteSW.x << ";y=" << pSpriteSW.y << "]" << std::endl;
                    }

                    /////////////
                    //SPRITE SE//
                    /////////////
                    //////////////////////////////////////////////////////////////////////////////
                    tSpriteSE.left = tRect.left + tSpriteSW.width;
                    tSpriteSE.top = tRect.top;
                    tSpriteSE.width = bound.width - tSpriteSW.width;
                    tSpriteSE.height = bound.height;
                    pSpriteSE.x = shapeSE.left;
                    pSpriteSE.y = bound.top;
                    spriteSE->setTextureRect(tSpriteSE);
                    spriteSE->setPosition(pSpriteSE);
                    //////////////////////////////////////////////////////////////////////////////
                    if(DEBUG)
                    {
                        std::cout << "spriteSE [tx=" << tSpriteSE.left << ";ty=" << tSpriteSE.top << ";w=" << tSpriteSE.width << ";h=" << tSpriteSE.height << "] [x=" << pSpriteSE.x << ";y=" << pSpriteSE.y << "]" << std::endl;
                    }
                    // On ajoute les 2 sprites splitté au quadrant père
                    if(DEBUGLOCAL)
                    {
                        std::cout << "Ajout dans SW - SE" << std::endl;
                    }
                    spl.SW = spriteSW;
                    spl.SE = spriteSE;
                    m_splitedElements.push_back(std::make_shared<SplitedSprite>(spl));
                    m_southWest->add(*spriteSW);
                    m_southEast->add(*spriteSE);
                } else // Il est uniquement dans le quadrant SW
                {
                    if(DEBUG)
                    {
                        std::cout << "Ajout dans SW" << std::endl;
                    }
                    m_southWest->add(obj);
                }
            } else if (shapeSE.intersects(bound))
            {
                if(DEBUG)
                {
                    std::cout << "Ajout dans SE" << std::endl;
                }
                m_southEast->add(obj);
            }
            if(DEBUG)
            {
                std::cout << "*--END--*" << std::endl;
            }
            return true;
        }
        if(DEBUG)
        {
            std::cout << "*--END--*" << std::endl;
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
* \return vector of deleted objects
**/
std::vector<std::shared_ptr<sf::Sprite>> Quadtree::del(sf::FloatRect pos)
{
    if(DEBUG)
    {
        std::cout << "*-----*" << std::endl;
        std::cout << "*-DEL-*" << std::endl;
        std::cout << "*-----*" << std::endl << std::endl;
        std::cout << "pos [x=" << pos.left << ";y=" << pos.top << ";w=" << pos.width << ":h=" << pos.height << "]" << std::endl;
    }
    std::vector<std::shared_ptr<sf::Sprite>> delObjects = std::vector<std::shared_ptr<sf::Sprite>>();
    std::vector<std::shared_ptr<sf::Sprite>> answer = std::vector<std::shared_ptr<sf::Sprite>>();
    if(!m_shape.intersects(pos)) {
        answer.clear();
        return delObjects;
    }

    if(m_elements.empty() && !m_enable)
    {
        if(m_splitedElements.size() != 0)
        {
            answer = eraseSplitedElement(pos);
            delObjects.insert(delObjects.end(),answer.begin(),answer.end());
        }
        sf::FloatRect shapeNW = m_northWest->getShape();
        sf::FloatRect shapeNE = m_northEast->getShape();
        sf::FloatRect shapeSW = m_southWest->getShape();
        sf::FloatRect shapeSE = m_southEast->getShape();
        if(shapeNW.intersects(pos))
        {
            answer = m_northWest->del(pos);
            delObjects.insert(delObjects.end(),answer.begin(),answer.end());
        }
        if(shapeNE.intersects(pos))
        {
            answer = m_northEast->del(pos);
            delObjects.insert(delObjects.end(),answer.begin(),answer.end());
        }
        if(shapeSW.intersects(pos))
        {
            answer = m_southWest->del(pos);
            delObjects.insert(delObjects.end(),answer.begin(),answer.end());
        }
        if(shapeSE.intersects(pos))
        {
            answer = m_southEast->del(pos);
            delObjects.insert(delObjects.end(),answer.begin(),answer.end());
        }
        if(DEBUG)
        {
            std::cout << "-- Nbr Elem : " << m_northWest->nbElement() + m_northEast->nbElement() + m_southWest->nbElement() + m_southEast->nbElement() << "--" << std::endl;
        }
        if((m_northWest->nbElement() + m_northEast->nbElement() + m_southWest->nbElement() + m_southEast->nbElement()) <= QUAD_NODE_CAPACITY)
        {
           merge();
        }
    } else
    {
        std::vector<std::shared_ptr<sf::Sprite>>::iterator it = m_elements.begin();
        for( ; it != m_elements.end(); )
        {
            if((*it->get()).getGlobalBounds().intersects(pos))
            {
                if(DEBUG)
                {
                    std::cout << "Count of Shared Pointer : " << it->use_count() << std::endl;
                }
                delObjects.push_back(*it);
                if(DEBUG)
                {
                    std::cout << "Count of Shared Pointer after push : " << it->use_count() << std::endl;
                }
                it = m_elements.erase(it);
                if(DEBUG)
                {
                    std::cout << "Storage capacity : " << m_elements.capacity() << std::endl;
                }
            } else
            {
                ++it;
            }
        }
        m_elements.shrink_to_fit();
        if(DEBUG)
        {
            std::cout << "Storage capacity after del: " << m_elements.capacity() << std::endl;
        }
    }
    if(DEBUG)
    {
        std::cout << "*-----*" << std::endl;
        std::cout << "*-END-*" << std::endl;
        std::cout << "*-----*" << std::endl << std::endl;
    }
    answer.clear();
    return delObjects;
}

/**
*
* \fn queryRange(sf::FloatRect pos)
*
* \brief Search and return the vector of element around obj
*
* \param obj : The object on which we want to make query
* \return vector of element around obj. Return empty vector if obj is not in quadrant
**/
 std::vector<std::shared_ptr<sf::Sprite>> Quadtree::queryRange(sf::FloatRect pos)
{
    if(DEBUG)
    {
        std::cout << "*--------------*" << std::endl;
        std::cout << "* START QUERY  *" << std::endl;
        std::cout << "*--------------*" << std::endl;
        std::cout << "Query at [x=" << pos.left << ";y=" << pos.top << ";width=" << pos.width << ";height=" << pos.height << "]" << std::endl;
        std::cout << "On shape [x=" << m_shape.left << ";y=" << m_shape.top << ";width=" << m_shape.width << ";height=" << m_shape.height << "]" << std::endl;
    }
     std::vector<std::shared_ptr<sf::Sprite>> answer =  std::vector<std::shared_ptr<sf::Sprite>>();
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
        std::vector<std::shared_ptr<sf::Sprite>> tmp = std::vector<std::shared_ptr<sf::Sprite>>();
        if(m_northWest->getShape().intersects(pos))
        {
            tmp = m_northWest->queryRange(pos);
            answer.insert(answer.end(),tmp.begin(),tmp.end());
        }
        if (m_northEast->getShape().intersects(pos))
        {
            tmp = m_northEast->queryRange(sf::FloatRect(pos));
            answer.insert(answer.end(),tmp.begin(),tmp.end());
        }
        if (m_southWest->getShape().intersects(pos))
        {
            tmp = m_southWest->queryRange(sf::FloatRect(pos));
            answer.insert(answer.end(),tmp.begin(),tmp.end());
        }
        if (m_southEast->getShape().intersects(pos))
        {
            tmp = m_southEast->queryRange(sf::FloatRect(pos));
            answer.insert(answer.end(),tmp.begin(),tmp.end());
        }
        tmp.clear();
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
    if(!m_elements.empty())
    {
        if(DEBUG)
        {
            std::cout << "Le quad maitre à des elements" << std::endl;
        }
        for( std::vector<std::shared_ptr<sf::Sprite>>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
        {
            add(*it->get());
        }
        m_elements.clear();
        m_elements.shrink_to_fit();
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
* \brief Merge the quadtree when Sum(child element) < QUAD_NODE_CAPACITY and restore splitted sprite
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
        std::cout << "splited size : " << m_splitedElements.size() << std::endl;
    }
    std::vector<std::shared_ptr<SplitedSprite>>::iterator it = m_splitedElements.begin();
    int splitedSize = m_splitedElements.size();
    for(int i = 0; i < splitedSize; i++)
    {
        m_elements.push_back(m_splitedElements.at(0)->origin);
        eraseSplitedElement(m_splitedElements.at(0)->origin->getGlobalBounds());
    }
    if(DEBUG)
    {
        std::cout << "SplitedSprite done" << std::endl;
        std::cout << "m_element : " << m_elements.size() << std::endl;
    }
    std::vector<std::shared_ptr<sf::Sprite>> tmp;
    tmp = m_northWest->getElements();
    m_elements.insert(std::end(m_elements),std::begin(tmp),std::end(tmp));
    tmp = m_northEast->getElements();
    m_elements.insert(std::end(m_elements),std::begin(tmp),std::end(tmp));
    tmp = m_southWest->getElements();
    m_elements.insert(std::end(m_elements),std::begin(tmp),std::end(tmp));
    tmp = m_southEast->getElements();
    m_elements.insert(std::end(m_elements),std::begin(tmp),std::end(tmp));
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
* \fn eraseSplitedElement(sf::FloatRect pos)
*
* \brief Remove Deprecated Object (When tile is split into different quadrant)
*
* \param
* \return vector of deleted object
**/

 std::vector<std::shared_ptr<sf::Sprite>> Quadtree::eraseSplitedElement(sf::FloatRect pos)
{
    std::vector<std::shared_ptr<sf::Sprite>>delObjects = std::vector<std::shared_ptr<sf::Sprite>>();
    std::vector<std::shared_ptr<SplitedSprite>>::iterator it = m_splitedElements.begin();
    for( ; it != m_splitedElements.end(); )
    {
        if((*it->get()).origin->getGlobalBounds().intersects(pos))
        {
            delObjects.push_back((*it->get()).origin);
            if(DEBUGLOCAL)
            {
                sf::FloatRect rect = (*it->get()).origin->getGlobalBounds();
                std::cout << "Le sprite [x=" << rect.left << ";y=" << rect.top << ";w=" << rect.width << ";h=" << rect.height << "] est a supprimer" << std::endl;
            }
            if((*it->get()).NW != NULL)
            {
                if(DEBUGLOCAL)
                {
                    std::cout << "Suppression en NW" << std::endl;
                }
                m_northWest->del((*it->get()).NW->getGlobalBounds());
            }
            if((*it->get()).NE != NULL)
            {
                if(DEBUGLOCAL)
                {
                    std::cout << "Suppression en NE" << std::endl;
                }
                m_northEast->del((*it->get()).NE->getGlobalBounds());
            }
            if((*it->get()).SW != NULL)
            {
                if(DEBUGLOCAL)
                {
                    std::cout << "Suppression en SW" << std::endl;
                }
                m_southWest->del((*it->get()).SW->getGlobalBounds());
            }
            if((*it->get()).SE != NULL)
            {
                if(DEBUGLOCAL)
                {
                    std::cout << "Suppression en SE" << std::endl;
                }
                m_southEast->del((*it->get()).SE->getGlobalBounds());
            }
            if(DEBUG)
            {
                std::cout << "Shared pointer count : " << it->use_count() << std::endl;
            }
            it = m_splitedElements.erase(it);
        } else
        {
            ++it;
        }
    }
    m_splitedElements.shrink_to_fit();
    return delObjects;
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
        if(DEBUG)
        {
            for(std::vector<std::shared_ptr<sf::Sprite>>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
            {
                std::cout << "Count of Shared Pointer : " << it->use_count() << std::endl;
            }
        }
        m_elements.clear();
        m_splitedElements.clear();
        m_elements.shrink_to_fit();
        m_splitedElements.shrink_to_fit();
        if(DEBUG)
        {
            std::cout << "Storage capacity : " << m_elements.capacity() << std::endl;
        }
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
    if(m_elements.empty() && m_northWest != NULL && m_northEast != NULL && m_southWest != NULL && m_southEast != NULL)
    {
        m_northWest->draw(window);
        m_northEast->draw(window);
        m_southWest->draw(window);
        m_southEast->draw(window);
    } else
    {
        if(m_displayTile)
        {
            for(std::vector<std::shared_ptr<sf::Sprite>>::iterator it = m_elements.begin(); it != m_elements.end(); it++)
            {
                window->draw(*it->get());
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

/**
*
* \fn nbElement()
*
* \brief this function allow to get the number of element in this quadrant
*
* \param
* \return return the size of m_element
**/
int Quadtree::nbElement()
{
    if(m_enable)
    {
        return m_elements.size();
    } else
    {
        return m_northWest->nbElement() + m_northEast->nbElement() + m_southWest->nbElement() + m_southEast->nbElement();
    }

}
