#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>

#include "include/Character.hpp"
#include "include/Quadtree.hpp"
#include "include/Engine.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Proto Movement & Grabity", sf::Style::Default);
    window->setFramerateLimit(60);

    //Creation d'un personnage
    std::shared_ptr<Quadtree> world = std::make_shared<Quadtree>(Quadtree(0.0f,0.0f,window->getSize().x,window->getSize().y));
    std::shared_ptr<Engine> engine = std::make_shared<Engine>(Engine(world));
    Character* player = new Character("player.png",sf::IntRect(13,9,51,45),sf::Vector2f(20,20),engine);
    //Pour la creation de case random
    //Character player = Character("player.png",sf::IntRect(13,9,51,45),sf::Vector2f(20,20),engine);
    srand(time(NULL));
    bool m_add = true;

    sf::Texture txt;
    if(!txt.loadFromFile(defaultTilePath+"Tileset.png")){
        //RAISE A LOAD TEXTURE EXCEPTION
    }
    sf::Sprite spr;
    spr.setTexture(txt);
    spr.setTextureRect(sf::IntRect(416,192,SPRITE_HEIGHT,SPRITE_WIDTH));
    spr.setPosition(30,100);
    world->add(spr);
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
                                    sf::Sprite spr;
                                    spr.setTexture(txt);
                                    spr.setTextureRect(sf::IntRect(416,192,SPRITE_HEIGHT,SPRITE_WIDTH));
                                    spr.setPosition(rand()%window->getSize().x,rand()%window->getSize().y);
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
                            case sf::Keyboard::A :
                                (m_add)?m_add = false:m_add = true;
                                break;
                            case sf::Keyboard::P :
                                std::cout << "/WARNING\\ Delete world !" << std::endl;
                                world.reset();
                                std::cout << "WORLD DELETE" << std::endl;
                                world = std::make_shared<Quadtree>(Quadtree(0.0f,0.0f,window->getSize().x,window->getSize().y));
                                std::cout << "New world create" << std::endl;
                                break;
                            case sf::Keyboard::X :
                                std::cout << "Position of player : x = " << player->getPosition().x << "y : " << player->getPosition().y << std::endl;
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
                            {
                                if(m_add)
                                {
                                    sf::Sprite spr;
                                    spr.setTexture(txt);
                                    spr.setTextureRect(sf::IntRect(416,192,SPRITE_HEIGHT,SPRITE_WIDTH));
                                    spr.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y));
                                    world->add(spr);
                                } else
                                {
                                    std::vector<std::shared_ptr<sf::Sprite>> deletedObject =  world->del(sf::FloatRect(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y,32,32));
                                    std::cout << "Deleted object : " << std::endl;
                                    for(std::vector<std::shared_ptr<sf::Sprite>>::iterator it = deletedObject.begin(); it != deletedObject.end(); it++)
                                    {
                                        std::cout << "Tile at [x=" << (*it)->getPosition().x << ";y=" << (*it)->getPosition().y << std::endl;
                                    }
                                    deletedObject.clear();
                                }
                            }
                            break;
                        case sf::Mouse::Right:
                            {
                                std::vector<std::shared_ptr<sf::Sprite>> query = world->queryRange(sf::FloatRect(sf::Mouse::getPosition(*window).x,sf::Mouse::getPosition(*window).y,32,32));
                                std::cout << "*---------*" << std::endl;
                                std::cout << "*  QUERY  *" << std::endl;
                                std::cout << "*---------*" << std::endl;
                                if(query.size() > 0)
                                {
                                    std::cout << "Il y a " << query.size() << " dans ce quadrant" << std::endl;
                                    for(std::vector<std::shared_ptr<sf::Sprite>>::iterator it = query.begin(); it != query.end(); it++)
                                    {
                                        std::cout << "Tile at [x=" << (*it)->getGlobalBounds().top << ":y=" << (*it)->getGlobalBounds().left << "]" << std::endl;
                                    }
                                } else
                                {
                                    std::cout << "Aucun tile dans le quadrant" << std::endl;
                                }
                                //delete query;
                                std::cout << "*-------------*" << std::endl;
                                std::cout << "*  FIN QUERY  *" << std::endl;
                                std::cout << "*-------------*" << std::endl;
                            }
                            break;
                        default:
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
            player->move(sf::Vector2f(5,0));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            player->move(sf::Vector2f(-5,0));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            player->move(sf::Vector2f(0,-5));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            player->move(sf::Vector2f(0,5));
        }

        window->clear();
        player->draw(window);
        world->draw(window);
        window->display();
    }

    //player.reset();
    world.reset();
    delete window;
    return 0;
}
