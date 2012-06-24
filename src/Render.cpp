#include "Render.h"

namespace guiml
{
	Render::Render(Widget *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage, int maxValueVertical, int maxValueHorizontalSlide) : Widget(parent, rect), m_backgroundColor(backgroundColor), m_backgroundImage(backgroundImage), m_maxValueVerticalSlide(maxValueVertical), m_maxValueHorisontalSlide(maxValueHorizontalSlide)
	{
/*  	m_verticalSlide.setParent(this);
		m_horizontalSlide.setParent(this);

		m_horizontalSlide.setPosition(Position::HORIZONTAL);

		m_verticalSlide.setValue(sf::Vector2f(0, m_maxValueVerticalSlide));
		m_horizontalSlide.setExtremValue(sf::Vector2f(0, m_maxValueHorisontalSlide));

		m_verticalSlide.setRect(sf::FloatRect(m_size.x - m_size.x/100, 0, m_size.x / 100, m_size.y));
		m_hozirontalSlide.setRect(sf::FloatRect(0, m_size.y - m_size.y/100, m_size.x, m_size.y/100));
		if(m_verticalSlide > 0)
			m_verticalSlide.drawWidget(false);
		if(m_horizontalSlide > 0)
			m_horizontalSlide.drawWidget(false);
		*/
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

	void Render::moveView(const sf::Vector2f &move)
	{
		moveView(move.x, move.y);
	}

	void Render::moveView(int x, int y)
	{
		m_renderView.move(x, y);
		setView(m_renderView);
	}

	void Render::resizeView(const sf::Vector2f& size)
	{
		resizeView(size.x, size.y);
	}

	void Render::resizeView(int x, int y)
	{
		m_renderView.setSize(x, y);
		setView(m_renderView);
	}

	void Render::setViewPosition(const sf::Vector2f& position)
	{
		setViewPosition(position.x, position.y);
	}

	void Render::setViewPosition(int x, int y)
	{
		setRectView(sf::FloatRect(x, y, m_renderView.getSize().x, m_renderView.getSize().y));
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
