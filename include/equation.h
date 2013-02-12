#ifndef EQUATION
#define EQUATION

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

sf::Vector2f circle(const float x, const float centerx, const float centery, const float size);
bool rectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2);

#endif
