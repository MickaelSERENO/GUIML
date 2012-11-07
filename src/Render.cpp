#include "Render.h"

namespace guiml
{
	Render::Render(Updatable *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage) : Widget(parent, rect), IRender(), m_backgroundColor(backgroundColor)
	{
		setBackgroundImage(backgroundImage);
	}

	void Render::updateFocus()
	{
		if(m_event && m_event->isMouseInRect(getRect()))
			Updatable::updateFocus();
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

	void Render::setViewSize(const sf::Vector2f& size)
	{
		setViewSize(size.x, size.y);
	}

	void Render::setViewSize(float x, float y)
	{
		m_renderView.setSize(x, y);
		setView(m_renderView);
	}

	void Render::setViewPosition(float x, float y)
	{
		m_renderView.setCenter(x + m_renderView.getSize().x/2, y + m_renderView.getSize().y/2);
		setView(m_renderView);
	}

	void Render::setViewport(const sf::FloatRect& rect)
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

	sf::Vector2f Render::getViewPosition() const
	{
		return sf::Vector2f(m_renderView.getCenter().x - m_renderView.getSize().x/2, m_renderView.getCenter().y - m_renderView.getSize().y/2);
	}

	bool Render::isInView(const sf::FloatRect &rect) const
	{
		sf::Vector2f viewPos = m_renderView.getCenter();
		sf::Vector2f viewSize = m_renderView.getSize();
		viewPos.x -= viewSize.x/2;
		viewPos.y -= viewSize.y/2;

		if(rect.left + rect.width <= viewPos.x
			||rect.left >= viewPos.x + viewSize.x
			||rect.top + rect.height <= viewPos.y
			||rect.top >= viewPos.y + viewSize.y)
			return false;
		return true;
	}
}
