#include "Window.h"
#include "Layout.h"
#include "Button.h"

int main()
{
	guiml::Window window(sf::VideoMode(800, 600, 32), std::string("teste"), NULL, 60, sf::Color::Black, guiml::Image(NULL, std::string("background.jpg")));
	sf::Sprite sprite;
	sprite.setColor(sf::Color(10, 10, 10));
	std::cout << sprite.getColor().r << " " << sprite.getColor().g << " " << sprite.getColor().b << " " << sprite.getColor().a << std::endl;

	while(window.isOpen())
	{
		window.update();
	}
}
