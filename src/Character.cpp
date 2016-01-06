#include "../include/Character.hpp"

/**
*
* \fn Character(std::string path)
*
* \brief Basic constructor of Character
*
* \param path : Path of sprite character
* \return
**/
Character::Character(std::string path)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAULT_SPEED;
    // On charge la texture
    if(!m_texture.loadFromFile(defaultCharPath+path)){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(sf::IntRect(13,9,51,45));

    // Position initial du joueur
    m_position.x = 20;
    m_position.y = 20;
}

/**
*
* \fn ~Character()
*
* \brief Basic destructor of Character
*
* \param
* \return
**/
Character::~Character()
// TODO : Destructeur de la classe personnage.
{
    //dtor
}

/**
* \fn draw(sf::RenderWindow* window)
*
* \brief Draw character on window
*
* \param window : The RenderWindow
* \return void
**/
void Character::draw(sf::RenderWindow* window)
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
void Character::update(sf::RenderWindow* window)
// TODO : Fonction qui permet de mettre à jour le personnage dans la fenetre
{
    m_sprite.setPosition(m_position);
}

/**
* \fn move(sf::Vector2f motion, Quadtree* universe)
*
* \brief Move character if possible and correct
*
* \param motion : Motion Vector, universe : Quadtree which represents world
* \return void
**/
void Character::move(sf::Vector2f motion, Quadtree* universe)
{
    if (Engine::move(m_sprite,motion,universe))
    {
        m_position += motion;
    }
}


/**
* \fn jump(sf::Vector2f motion, Quadtree* universe)
*
* \brief Jump character if possible and correct
*
* \param motion : Motion Vector, universe : Quadtree which represents world
* \return void
**/
/*void Character::jump(sf::Vector2f motion, Quadtree* universe)
{

}*/

