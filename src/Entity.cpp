#include "../include/Entity.hpp"

Entity::Entity(std::string path, sf::IntRect textRect)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAULT_SPEED;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(textRect);

    // Position initial de l'entité
    m_position.x = 20;
    m_position.y = 20;

    m_time = 0;
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
    update(window);
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
void Entity::update(sf::RenderWindow* window)
// TODO : Fonction qui permet de mettre � jour le personnage dans la fenetre
{
    m_sprite.setPosition(m_position);
}

void Entity::setMotion(sf::Vector2f motion)
{
    m_motion = motion;
}


/**
* \fn move(sf::Vector2f motion, Quadtree* universe)
*
* \brief Move character if possible and correct
*
* \param motion : Motion Vector, universe : Quadtree which represents world
* \return void
**/
/*void Entity::move(sf::Vector2f motion, Quadtree* universe)
{
    Engine::move(this,motion,universe);
}*/

