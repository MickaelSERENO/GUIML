#include "Render.h"

namespace guiml
{
	Render::Render(Widget *parent, const sf::IntRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage) : Widget(parent, rect), m_backgroundColor(backgroundColor), m_backgroundImage(backgroundImage)
	{
		setView(m_renderView);
	}

	void Render::setBackgroundImage(const Image &backgroundImage)
	{
		m_backgroundImage = backgroundImage;
		m_backgroundImage.setRect(getRect());
		m_backgroundImage.setParent(this, 0);
	}

	void Render::setBackgroundColor(const sf::Color &backgroundColor)
	{
		m_backgroundColor = backgroundColor;
	}

	void Render::setTitle(const std::string &title)
	{
		m_windowTitle = title;
	}

	void Render::setView(const sf::View &view)
	{
		m_renderView = view;
	}

	void Render::moveView(const sf::Vector2i &move)
	{
		moveView(move.x, move.y);
	}

	void Render::moveView(int x, int y)
	{
		m_renderView.move(x, y);
		setView(m_renderView);
	}

	const Image& Render::getBackgroundImage() const
	{
		return m_backgroundImage;
	}

	const sf::Color& Render::getBackgroundColor() const
	{
		return m_backgroundColor;
	}

	const std::string& Render::getTitle() const
	{
		return m_windowTitle;
	}

	const sf::View& Render::getView() const
	{
		return m_renderView;
	}

	sf::FloatRect Render::getViewport() const
	{
		return m_renderView.getViewport();
	}
}
