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
Character::Character(std::string path, sf::IntRect textRect) :
Entity(path,textRect)
{
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
