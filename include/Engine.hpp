#ifndef ENGINE_HPP
#define ENGINE_HPP
#include <memory>
#include "Entity.hpp"
#include "Quadtree.hpp"



class Engine
{
    public:
        Engine(std::shared_ptr<Quadtree> universe);
        virtual ~Engine();
        bool collisionAABB(sf::FloatRect box1, sf::FloatRect box2);
        bool isAbleToMove(sf::FloatRect box);
        bool isAbleToJump(sf::FloatRect box);
    protected:
    private:
        std::shared_ptr<Quadtree> m_universe;

};

#endif // ENGINE_HPP
