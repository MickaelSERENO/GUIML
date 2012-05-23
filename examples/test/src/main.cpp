#include "Widget.h"
#include "Button.h"
#include "Window.h"
#include "Frame.h"
#include <iostream>

int main()
{
	guiml::Window window(sf::VideoMode(800, 600), "teste");
	guiml::Frame frame(&window, sf::IntRect(100, 100, 550, 400), sf::Color(0, 255, 255), guiml::Image(), guiml::Label(NULL, std::string("Teste")), sf::Color(255, 0, 0));
	guiml::Label label(NULL, std::string("Sa marche"));
	guiml::Button button(&frame, label, sf::IntRect(40, 14, 250, 160));
	while(window.isOpen())
	{
		if(button.isActived())
			std::cout << "1" << std::endl;
		window.update();
	}
	return 0;
}
