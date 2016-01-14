#include "Utility.hpp"

sf::Vector2f realityToUniverse(sf::FloatRect box, float hScreen)
{
    return sf::Vector2f(box.left,hScreen-(box.top + box.height));
}

sf::Vector2f realityToUniverse(sf::Vector2f pos, float hSprite, float hScreen)
{
    return sf::Vector2f(pos.x,hScreen-(pos.y + hSprite));
}

sf::Vector2f realityMotionToUniverse(sf::Vector2f motion)
{
    return sf::Vector2f(motion.x,-motion.y);
}

sf::Vector2f universeToReality(sf::FloatRect box, float hScreen)
{
    return sf::Vector2f(box.left,hScreen-(box.top + box.height));
}

sf::Vector2f universeToReality(sf::Vector2f pos, float hSprite, float hScreen)
{
    return sf::Vector2f(pos.x,hScreen-(pos.y + hSprite));
}

sf::Vector2f universeMotionToReality(sf::Vector2f motion)
{
    return sf::Vector2f(motion.x,-motion.y);
}
