#include "../include/Entity.hpp"

Entity::Entity(std::string path, sf::IntRect textRect, sf::Vector2f initPos, std::shared_ptr<Engine> engine)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAULT_SPEED;
    m_engine = engine;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
        std::cerr << "Error on load texture" << std::endl;
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(textRect);

    m_width = textRect.width;
    m_height = textRect.height;
    // Position absolu initial de l'entité
    m_positionReal = universeToReality(initPos,m_height);


    m_time = 1;
    //m_onShifting = false;
}

Entity::~Entity()
{
    //dtor
}

/**
* \fn draw(sf::RenderWindow* window)
*make_unique
* \brief Draw character on window
*
* \param window : The RenderWindow
* \return void
**/
void Entity::draw(sf::RenderWindow* window)
// TODO : Fonction qui permet de dessiner le personnage dans la fenetre
{
    update();
    window->draw(m_sprite);
}

/**
* \fn update(sf::RenderWindow* window)
*
* \brief Update character on window
*
* \param window : The RenderWindow
* \return void
**/
void Entity::update()
// TODO : Fonction qui permet de mettre � jour le personnage dans la fenetre
{
    //if(m_onShifting)
    //{
    shifting();
    //}
    m_sprite.setPosition(realityToUniverse(m_positionReal,m_height));
}

/*void Entity::setMotion(sf::Vector2f motion)
{
    m_motion = motion;
}*/

/**
* \fn move(sf::Vector2f motion)
*
* \brief Move character if possible and correct
*
* \param motion : Motion Vector
* \return void
**/
void Entity::move(sf::Vector2f motion)
{
    if(m_motion.y == 0)
    {
        addMotion(motion);
    }
}

/**
* \fn jump(sf::Vector2f motion)
*
* \brief Jump character if possible and correct
*
* \param motion : Motion Vector
* \return void
**/
/*void Entity::jump(sf::Vector2f motion)
{
    if(m_motion.y == 0)
    {
        addMotion(motion);
    }
}*/

/**
* \fn shifthing()
*
* \brief Manage the shifting of entity
*
* \param
* \return void
**/
void Entity::shifting()
{
    if(m_motion.x == 0 && m_motion.y == 0)
    {
        //m_onShifting = false;
        m_time = 1;
    }
    m_time += 10;
    double hSpeed = cos(PI/3) * m_motion.x;
    double vSpeed = sin(PI/3) * m_motion.y;
    sf::Vector2f motion;
    sf::Vector2f nextPos;
    motion.x = (float)(hSpeed*m_time);
    motion.y = (float)((vSpeed*m_time)-((DEFAULT_GRAVITY*pow(m_time,2.0))/2000.0));
    nextPos = realityToUniverse(m_positionReal + motion,m_height);

    if (m_engine->isAbleToMove(sf::FloatRect(nextPos.x,nextPos.y,m_height,m_width)))
    { /** TODO **/
        m_positionReal = universeToReality(nextPos,m_height);
    } else
    {
        //m_positionAbs.y = nextPos.y;
    }
    m_motion -= motion;

}

