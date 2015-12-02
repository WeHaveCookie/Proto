#include "../include/Character.hpp"

Character::Character(std::string path)
{
    m_gravity = DEFAULT_GRAVITY;
    m_speed = DEFAUTL_SPEED;
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

Character::~Character()
// TODO : Destructeur de la classe personnage.
{
    //dtor
}

void Character::draw(sf::RenderWindow* window)
// TODO : Fonction qui permet de dessiner le personnage dans la fenetre
{
    update(window);
    window->draw(m_sprite);
}

void Character::update(sf::RenderWindow* window)
// TODO : Fonction qui permet de mettre à jour le personnage dans la fenetre
{

}

