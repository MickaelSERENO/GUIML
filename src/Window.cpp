#include "Window.h"

namespace guiml
{
	Window::Window(const sf::VideoMode &mode, const std::string &title, Updatable *parent, unsigned int framerateLimit, const sf::Color &backgroundColor, const Image &backgroundImage) : Render(parent, sf::FloatRect(0, 0, mode.width, mode.height), backgroundColor, backgroundImage), sf::RenderWindow(mode, title), m_framerate(framerateLimit)
	{
		m_isStaticToView = false;
		RenderWindow::setPosition(sf::Vector2i(0, 0));
		setFramerateLimit(framerateLimit);
		m_event = new EventManager(this);
		resetView();
		clear(backgroundColor);
	}	

	Window::~Window()
	{
		delete m_event;
	}

	void Window::update()
	{
		update(*this);
	}

	void Window::update(IRender &render)
	{
		m_event->update();
		if(m_event->windowIsResize())
			Widget::resizeWidget(m_event->getDefaultWindowSize(), m_event->getNewWindowSize());
		m_framerate = 1 / (m_event->getElapsedTime() * 0.001);

		clear(m_backgroundColor);
		if(!m_parent)
			Widget::widgetMouseSelect=NULL;

		Widget::update(*this);
		display();
	}

	void Window::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
	{
		sf::RenderWindow::draw(drawable, states);
	}

	void Window::setPosition(float x, float y)
	{
		RenderWindow::setPosition(sf::Vector2i(x, y));
		Widget::setPosition(x, y);
	}

	void Window::setSize(float x, float y)
	{
		RenderWindow::setSize(sf::Vector2u(x, y));
		Widget::setSize(x, y);
		m_event->setDefaultWindowSize(m_size);
	}

	void Window::setParent(Updatable* parent, int pos)
	{
		EventManager* event = m_event;
		Updatable::setParent(parent, pos);
		m_event = event;
		event=NULL;
	}

	void Window::setTitle(const std::string &title)
	{
		Render::setTitle(title);
		sf::RenderWindow::setTitle(title);
	}

	void Window::setView(const sf::View &view)
	{
		sf::RenderWindow::setView(view);
		Render::setView(view);
	}
	
	void Window::resetView()
	{
		setView(sf::RenderWindow::getDefaultView());
	}

	unsigned int Window::getFramerate()
	{
		return m_framerate;
	}

	EventManager* Window::getEventManagerFromRootParent() const
	{
		return m_event;
	}

	void Window::resizeWidget(const sf::Vector2f& defaultWindowSize, const sf::Vector2f& newWindowSize)
	{
		return;
	}
}
