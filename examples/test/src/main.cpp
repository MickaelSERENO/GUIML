#include "Widget.h"
#include "Button.h"
#include "Window.h"
#include "Frame.h"
#include "equation.h"
#include <iostream>

int main()
{
	guiml::Window window(sf::VideoMode(800, 600), "teste");
	guiml::Image image(&window, std::string("rectangle.jpg"));
	image.roundEdge(30);

	while(window.isOpen())
	{
		window.update();
	}
	return 0;
}
