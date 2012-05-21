#ifndef DEF_WINDOW
#define DEF_WINDOW

#include "EventManager.h"
#include "Image.h"
#include "Render.h"

namespace guiml
{
	class Window : public Render, public sf::RenderWindow
	{
	public:
		Window(const sf::VideoMode &mode, const std::string &title, Widget *parent = NULL, unsigned int framerateLimit = 60, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image());
		virtual ~Window();

		void update();
		void update(std::list<sf::Drawable*> &drawable); //update all widgets and the event
		void show(std::list<sf::Drawable*> &drawable); //draw the window

		void setPosition(int x, int y);
		void setSize(int x, int y);
		virtual void setTitle(const std::string &title);
		void setView(const sf::View &view);
		void resetView();

		virtual EventManager* getEventManager() const;
		unsigned int getFramerate();
		virtual void resizeWidget(const sf::Vector2i& defaultWindowSize, const sf::Vector2i& newWindowSize);
	protected:
		EventManager *m_event;
		float m_framerate;
	};
}

#endif
