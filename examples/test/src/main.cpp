#include "Window.h"
#include "Button.h"

int main()
{
	guiml::Window window(sf::VideoMode(800, 600), std::string("teste"), NULL, 60, sf::Color::Black, guiml::Image(NULL, std::string("background.jpg")));
	guiml::Image image(&window, std::string("rectangle.jpg"));
	image.roundEdge(50);
	while(window.isOpen())
	{
		window.update();
	}
}
