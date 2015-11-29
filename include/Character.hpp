#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include <SFML/Graphics.hpp>
#include "Constante.hpp"
#include "DrawableObject.hpp"

class Character : public DrawableObject
{
public:
    Character(std::string path);
    void draw(sf::RenderWindow* window);
    void update(sf::RenderWindow* window);
    virtual ~Character();
protected:
private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Vector2f m_position;
    float m_gravity;
    float m_speed;
};

#endif // CHARACTER_HPP
