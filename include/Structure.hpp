#ifndef STRUCTURE_H
#define STRUCTURE_H
#include <list>
#include <memory>
#include <SFML/Graphics.hpp>

struct SplitedSprite
{
    std::shared_ptr<sf::Sprite> origin;
    std::shared_ptr<sf::Sprite> NW;
    std::shared_ptr<sf::Sprite> NE;
    std::shared_ptr<sf::Sprite> SW;
    std::shared_ptr<sf::Sprite> SE;
};

#endif // STRUCTURE_H
