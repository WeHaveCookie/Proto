#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include "DrawableObject.hpp"
#include "Quadtree.hpp"
//#include "Engine.hpp"
#include "Constante.hpp"

class Engine;

class Entity : public DrawableObject
{
    public:
        Entity(std::string path, sf::IntRect textRect);
        virtual ~Entity();
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        //void move(sf::Vector2f motion, Quadtree* universe);
        // Getteur & Setteur //
        void setMotion(sf::Vector2f motion);
        inline sf::Vector2f getMotion(){return m_motion;}
        inline sf::Sprite getSprite() {return m_sprite;}
    protected:
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_position;
        sf::Vector2f m_motion;
        float m_gravity;
        float m_speed;
        float m_time;
};

#endif // ENTITY_HPP
