#ifndef EQUATION
#define EQUATION

#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>

sf::Vector2f circle(const float x, const float centerx, const float centery, const float size);

template <typename T>
bool rectCollision(const sf::Rect<T> &rect1, const sf::Rect<T> &rect2)
{
	if(rect1.left + rect1.width <= rect2.left
		||rect1.left >= rect2.left + rect2.width
		||rect1.top + rect1.height <= rect2.top
		||rect1.top >= rect2.top+rect2.height)
		return false;
	return true;
}

#endif
