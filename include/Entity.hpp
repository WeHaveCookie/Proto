#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <memory>
#include <math.h>
#include "DrawableObject.hpp"
//#include "Quadtree.hpp"
#include "Engine.hpp"
#include "Constante.hpp"
#include "Utility.hpp"

class Engine;

class Entity : public DrawableObject
{
    public:
        Entity(std::string path, sf::IntRect textRect, sf::Vector2f initPos, std::shared_ptr<Engine> engine);
        virtual ~Entity();
        void draw(sf::RenderWindow* window);
        void update();
        void move(sf::Vector2f motion);
        void shifting();
        //void jump(sf::Vector2f motion);

        // Getteur & Setteur //
        //void setMotion(sf::Vector2f motion);
        inline sf::Vector2f getMotion(){return m_motion;}
        inline sf::Vector2f getPosition(){return m_sprite.getPosition();}
        inline sf::Sprite getSprite() {return m_sprite;}
    protected:
        inline void addMotion(sf::Vector2f motion) {m_motion += motion; /*m_onShifting = true;*/}
        sf::Texture m_texture;
        sf::Sprite m_sprite;
        sf::Vector2f m_positionReal;
        sf::Vector2f m_motion;
        std::shared_ptr<Engine> m_engine;
        float m_width;
        float m_height;
        float m_gravity;
        float m_speed;
        float m_time;
        bool m_onShifting;
    private:

};

#endif // ENTITY_HPP
