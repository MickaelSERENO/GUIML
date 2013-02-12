#include <equation.h>

sf::Vector2f circle(const float x, const float centerx, const float centery, const float size)
{
	float y1 = (2*centery + sqrt(4*(-(x-centerx)*(x-centerx)+size*size)))/2;
	float y2 = (2*centery - sqrt(4*(-(x-centerx)*(x-centerx)+size*size)))/2;
	return sf::Vector2f(y1, y2);
}

bool rectCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
	if(rect1.left + rect1.width <= rect2.left
		||rect1.left >= rect2.left + rect2.width
		||rect1.top + rect1.height <= rect2.top
		||rect1.top >= rect2.top+rect2.height)
		return false;
	return true;
}
