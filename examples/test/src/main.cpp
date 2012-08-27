#include "Window.h"
#include "Layout.h"
#include "Button.h"
#include "Frame.h"
#include "CheckBox.h"

int main()
{
	guiml::Window window(sf::VideoMode(800, 600, 32), std::string("teste"), NULL, 60, sf::Color::Black, guiml::Image());
	guiml::CheckBox box(&window, sf::FloatRect(0, 0, 50, 50));

	while(window.isOpen())
	{
		window.update();
	}
}
