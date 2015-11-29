#ifndef DRAWABLEOBJECT_HPP
#define DRAWABLEOBJECT_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class DrawableObject
{
    public:
        DrawableObject();
        virtual ~DrawableObject();
    protected:
        virtual void draw(sf::RenderWindow* window) = 0;
        virtual void update(sf::RenderWindow* window) = 0;
    private:
};

#endif // DRAWABLEOBJECT_HPP
