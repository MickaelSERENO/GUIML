#include "Widget.h"
#include "Button.h"
#include "Window.h"
#include "Frame.h"
#include "equation.h"
#include <iostream>

int main()
{
	sf::Vector2f vector = circle(0, 3, 3, 20);
	std::cout << vector.x << " " << vector.y << std::endl;
	guiml::Window window(sf::VideoMode(800, 600), "teste");
	guiml::Frame frame(&window, sf::FloatRect(100, 100, 550, 400), sf::Color(0, 255, 255), guiml::Image(), guiml::Label(NULL, std::string("Teste")), sf::Color(255, 0, 0));
	guiml::Label label(NULL, std::string("Sa marche"));
	guiml::Button button(&frame, label, sf::FloatRect(40, 14, 100, 40));
	button.move(100, 100);
	while(window.isOpen())
	{
		if(button.isActived())
			std::cout << "1" << std::endl;
		window.update();
	}
	return 0;
}
