#include "Render.h"

namespace guiml
{
	Render::Render(Updatable *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage) : Widget(parent, rect), IRender(), m_backgroundColor(backgroundColor)
	{
		setBackgroundImage(backgroundImage);
		m_focus = false;
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
		sf::Vector2f back = getRenderViewPosition();
		m_renderView = view;

		std::list<Widget*> widgetChild = extractFromUpdatableChild<Widget>();	
		for(std::list<Widget*>::const_iterator it = widgetChild.begin(); it != widgetChild.end(); ++it)
			if((*it)->isStaticToView())
				(*it)->setPosition((*it)->getVirtualPosition() - back);
	}

	void Render::moveView(const sf::Vector2f &move)
	{
		moveView(move.x, move.y);
	}

	void Render::moveView(float x, float y)
	{
		sf::View view = m_renderView;
		view.move(x,y);
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

	const sf::FloatRect& Render::getViewport() const
	{
		return m_renderView.getViewport();
	}

	sf::FloatRect Render::getViewRect() const
	{
		return sf::FloatRect(getRenderViewPosition(), m_renderView.getSize());
	}

	sf::Vector2f Render::getRenderViewPosition() const
	{
		return sf::Vector2f(m_renderView.getCenter().x - m_renderView.getSize().x/2, m_renderView.getCenter().y - m_renderView.getSize().y/2);
	}

	sf::Vector2f Render::getSommeViewPosition() const
	{
		return sf::Vector2f(Updatable::getRenderViewPositionOnScreen().x + getRenderViewPosition().x, Updatable::getRenderViewPositionOnScreen().y + getRenderViewPosition().y);
	}

  	bool Render::isInView(const sf::FloatRect& rect) const
	{
		return rectCollision(rect, getViewRect());
	}

	sf::Vector2f Render::getRenderViewPositionOnScreen() const
	{
		return getSommeViewPosition();
	}
}
