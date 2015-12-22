#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
#include "include/Character.hpp"
#include "Quadtree.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);

    //Creation d'un personnage
    Character* player = new Character("player.png");
    Quadtree* world = new Quadtree(0.0f,0.0f,window->getSize().x,window->getSize().y);

    //Pour la creation de case random
    srand(time(NULL));

    std::vector<sf::Sprite*> vectCase;

    //world->subdivide();
    //world->add(&spr);
    sf::Texture txt;
    sf::Sprite* spr;
    if(!txt.loadFromFile(defaultTilePath+"Tileset.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    while (window->isOpen())
    {
        // On catch les events
        sf::Event event;
        while (window->pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed :
                    window->close();
                    break;
                case sf::Event::KeyPressed :
                    {
                        switch(event.key.code)
                        {
                            case sf::Keyboard::Escape :
                                window->close();
                                break;
                            case sf::Keyboard::J :
                                {
                                    spr = new sf::Sprite;
                                    spr->setTexture(txt);
                                    spr->setTextureRect(sf::IntRect(416,192,SPRITE_HEIGHT,SPRITE_WIDTH));
                                    spr->setPosition(rand()%window->getSize().x,rand()%window->getSize().y);
                                    world->add(spr);
                                }
                                break;
                            case sf::Keyboard::K :
                                {
                                    if(world->isDisplayTile()) {
                                        world->displayTile(false);
                                    } else
                                    {
                                        world->displayTile(true);
                                    }
                                }
                                break;
                            case sf::Keyboard::C :
                                world->clear();
                                break;
                            default :
                                break;
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed :
                    {
                        switch(event.mouseButton.button)
                        {
                        case sf::Mouse::Left :
                            world->del(sf::Vector2f(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y));
                            break;
                        }
                    }
                    break;
                default :
                    break;
            }
        }

        // On gère les event clavier hors du catch pour permettre la fluidite des deplacements
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


        window->clear();
        player->draw(window);
        world->draw(window);
        window->display();
    }

    return 0;
}
