#include "Window.h"
#include "Layout.h"
#include "Button.h"
#include "Frame.h"

int main()
{
	guiml::Window window(sf::VideoMode(800, 600, 32), std::string("teste"), NULL, 60, sf::Color::Black, guiml::Image());
	guiml::Frame frame(&window, sf::FloatRect(0, 0, 400, 300), sf::Color::Blue);

	while(window.isOpen())
	{
		window.update();
	}
}
