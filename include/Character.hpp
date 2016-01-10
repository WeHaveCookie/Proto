#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "Entity.hpp"

class Character : public Entity
{
public:
    Character(std::string path, sf::IntRect textRect);
    virtual ~Character();
protected:
private:
};

#endif // CHARACTER_HPP
