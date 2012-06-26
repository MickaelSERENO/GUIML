#include "Render.h"

namespace guiml
{
	Render::Render(Widget *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage) : Widget(parent, rect), m_backgroundColor(backgroundColor), m_backgroundImage(backgroundImage)
	{}

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
		m_renderTitle = title;
	}

	void Render::setView(const sf::View &view)
	{
		m_renderView = view;
	}

	void Render::moveView(const sf::Vector2f &move)
	{
		moveView(move.x, move.y);
	}

	void Render::moveView(float x, float y)
	{
		m_renderView.move(x, y);
		setView(m_renderView);
	}

	void Render::resizeView(const sf::Vector2f& size)
	{
		resizeView(size.x, size.y);
	}

	void Render::resizeView(float x, float y)
	{
		m_renderView.setSize(x, y);
		setView(m_renderView);
	}

	void Render::setViewPosition(const sf::Vector2f& position)
	{
		setViewPosition(position.x, position.y);
	}

	void Render::setViewPosition(float x, float y)
	{
		sf::FloatRect rect = m_renderView.getViewport();
		move(x - rect.left, y - rect.top);
	}

	void Render::setRectView(const sf::FloatRect& rect)
	{
		m_renderView.setViewport(rect);
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
		return m_renderTitle;
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
