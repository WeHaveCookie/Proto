#ifndef ENGINE_HPP
#define ENGINE_HPP
#include "Structure.hpp"
#include "Quadtree.hpp"

#define DEBUG 0

class Engine
{
    public:
        Engine();
        virtual ~Engine();
        static bool collisionAABB(sf::FloatRect box1, sf::FloatRect box2);
        static bool move(sf::Sprite box1, sf::Vector2f motion, Quadtree* universe);
        /*bool jump(sf::FloatRect box1, sf::Vector2f motion, Quadtree* universe);*/
    protected:
    private:

};

#endif // ENGINE_HPP
