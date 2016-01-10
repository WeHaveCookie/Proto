#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Entity.hpp"
#include "Quadtree.hpp"


class Engine
{
    public:
        Engine();
        virtual ~Engine();
        static bool collisionAABB(sf::FloatRect box1, sf::FloatRect box2);
        static void move(Entity* e, sf::Vector2f motion, Quadtree* universe);
        static void jump(Entity* e, sf::Vector2f motion, Quadtree* universe);
    protected:
    private:

};

#endif // ENGINE_HPP
