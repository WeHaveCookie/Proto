#ifndef UTILITY_HPP
#define UTILITY_HPP
#include <SFML/Graphics.hpp>


sf::Vector2f realityToUniverse(sf::FloatRect box);
sf::Vector2f realityToUniverse(sf::Vector2f pos, float h);

sf::Vector2f universeToReality(sf::FloatRect box);
sf::Vector2f universeToReality(sf::Vector2f pos, float h);

#endif // UTILITY_HPP
