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
    m_sprite.setPosition(initPos);

    m_width = textRect.width;
    m_height = textRect.height;
    // Position absolu initial de l'entité
    m_positionReal = universeToReality(initPos,m_height,m_engine->getUniverseSize().y);
    m_motion = sf::Vector2f(0.0,0.0);

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
    m_sprite.setPosition(realityToUniverse(m_positionReal,m_height,m_engine->getUniverseSize().y));
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
{ /** TODO **/
    if(m_motion.x <= 0 && m_motion.y >= 0)
    {
        //m_onShifting = false;
        m_time = 1;
    }
    m_time += 10;


    sf::Vector2f universeSize = m_engine->getUniverseSize();
    sf::Vector2f motionReal = universeMotionToReality(m_motion);
    sf::Vector2f motion;
    sf::Vector2f nextPos;


    if(DEBUG)
    {
        std::cout << "Current pos(Uni) : x=" << m_sprite.getPosition().x << " y=" << m_sprite.getPosition().y << std::endl;
        std::cout << "Current pos(real) : x=" << m_positionReal.x << " y=" << m_positionReal.y << std::endl;
        std::cout << "Motion(uni) : x=" << m_motion.x << " y=" << m_motion.y << std::endl;
        std::cout << "Motion(real) : x=" << motionReal.x << " y=" << motionReal.y << std::endl;
        std::cout << "Time : " << m_time << std::endl;
    }
    float angle = (m_motion.x == 0 && m_motion.y ==0)?0.0:acos(((m_positionReal.x + motionReal.x) - m_positionReal.x) / sqrt(pow((m_positionReal.x + motionReal.x) - m_positionReal.x,2.0)+pow((m_positionReal.y + motionReal.y) - m_positionReal.y,2.0)));
    if(DEBUG)
    {
        std::cout << "Angle : " << angle << std::endl;
    }


    double hSpeed = cos(angle) * motionReal.x;
    double vSpeed = sin(angle) * motionReal.y;

    motion.x = (float)(hSpeed*m_time);
    motion.y = (float)((vSpeed*m_time)-((DEFAULT_GRAVITY*pow(m_time,2.0))/2000.0));

    if(DEBUG)
    {
        std::cout << "New Motion(real) x=" << motion.x << "y=" << motion.y << std::endl;
    }

    nextPos = realityToUniverse(m_positionReal + motion,m_height,universeSize.y);

    if(DEBUG)
    {
        std::cout << "New Position(real) x=" << m_positionReal.x + motion.x << " y=" << m_positionReal.y + motion.y << std::endl;
        std::cout << "New Position(Uni) x=" << nextPos.x << " y=" << nextPos.y << std::endl;
    }
    if (m_engine->isAbleToMove(sf::FloatRect(nextPos.x,nextPos.y,m_height,m_width)))
    { /** TODO **/
        m_positionReal = universeToReality(nextPos,m_height,universeSize.y);
        if(DEBUG)
        {
            std::cout << "Pas de collision. Pos x=" << m_positionReal.x << " y=" << m_positionReal.y << std::endl;
        }
    } else
    { /** TODO **/
        if(DEBUG)
        {
            std::cout << "COLLISION NO CHANGE" << std::endl;
        }
        //m_positionAbs.y = nextPos.y;
    }
    m_motion -= motion;
    if(DEBUG)
    {
        std::cout << "New motion x=" << m_motion.x << " y=" << m_motion.y << std::endl;
    }

    std::string l;
    std::getline(std::cin,l);
}

