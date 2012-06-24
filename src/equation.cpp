#include <equation.h>

sf::Vector2f circle(const float x, const float centerx, const float centery, const float size)
{
	float y1 = (2*centery + sqrt(4*(-(x-centerx)*(x-centerx)+size*size)))/2;
	float y2 = (2*centery - sqrt(4*(-(x-centerx)*(x-centerx)+size*size)))/2;
	return sf::Vector2f(y1, y2);
}
