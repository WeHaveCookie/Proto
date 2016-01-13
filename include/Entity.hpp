#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <math.h>
#include "DrawableObject.hpp"
//#include "Quadtree.hpp"
#include "Engine.hpp"
#include "Constante.hpp"

class Engine;

class Entity : public DrawableObject
{
    public:
        Entity(std::string path, sf::IntRect textRect, sf::Vector2f initPos, std::shared_ptr<Engine> engine);
        virtual ~Entity();
        void draw(sf::RenderWindow* window);
        void update(sf::RenderWindow* window);
        void move(sf::Vector2f motion);
        void shifting();
        //void jump(sf::Vector2f motion);

        // Getteur & Setteur //
        //void setMotion(sf::Vector2f motion);
        inline sf::Vector2f getMotion(){return m_motion;}
        inline sf::Sprite getSprite() {return m_sprite;}
    protected:
        inline void addMotion(sf::Vector2f motion) {m_motion += motion; m_onShifting = true;}
    private:
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_positionAbs;
        sf::Vector2f m_motion;
        std::shared_ptr<Engine> m_engine;
        float m_gravity;
        float m_speed;
        float m_time;
        bool m_onShifting;
};

#endif // ENTITY_HPP
