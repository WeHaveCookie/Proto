#include "Utility.hpp"

sf::Vector2f realityToUniverse(sf::FloatRect box)
{
    return sf::Vector2f(box.left,-(box.top - box.height));
}

sf::Vector2f realityToUniverse(sf::Vector2f pos, float h)
{
    return sf::Vector2f(pos.x,-(pos.y - h));
}

sf::Vector2f universeToReality(sf::FloatRect box)
{
    return sf::Vector2f(box.left,-(box.top + box.height));
}

sf::Vector2f universeToReality(sf::Vector2f pos, float h)
{
    return sf::Vector2f(pos.x,-(pos.y + h));
}
