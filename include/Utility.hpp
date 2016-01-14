#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <SFML/Graphics.hpp>


sf::Vector2f realityToUniverse(sf::FloatRect box, float hScreen);
sf::Vector2f realityToUniverse(sf::Vector2f pos, float hSprite, float hScreen);
sf::Vector2f realityMotionToUniverse(sf::Vector2f motion);

sf::Vector2f universeToReality(sf::FloatRect box, float hScreen);
sf::Vector2f universeToReality(sf::Vector2f pos, float hSprite, float hScreen);
sf::Vector2f universeMotionToReality(sf::Vector2f motion);

#endif // UTILITY_HPP
