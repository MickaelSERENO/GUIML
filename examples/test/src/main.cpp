#include "Window.h"
#include "Layout.h"
#include "Button.h"

int main()
{
	guiml::Window window(sf::VideoMode(800, 600, 32), std::string("teste"), NULL, 60, sf::Color::Black, guiml::Image(NULL, std::string("background.jpg"), true));

	while(window.isOpen())
	{
		window.update();
	}
}
