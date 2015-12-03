#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "include/Character.hpp"
#include "Quadtree.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(200, 200), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);

    //Creation d'un personnage
    Character* player = new Character("player.png");
    Quadtree* world = new Quadtree();

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window->close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                player->move(sf::Vector2f(1,0),world);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                player->move(sf::Vector2f(-1,0),world);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            {
                player->move(sf::Vector2f(0,-1),world);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                player->move(sf::Vector2f(0,1),world);
            }

        }

        window->clear();
        player->draw(window);
        window->display();
    }

    return 0;
}
