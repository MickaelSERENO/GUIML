#include "Slide.h"

namespace guiml
{
	Slide::Slide(Updatable *parent, const sf::Vector2f &extremesValues, const sf::FloatRect &rect, int cursorSize, const Position& position, int pourcentageGlobalRectangle) : Widget(parent, rect), m_cursor(this), m_buttonUp(this), m_buttonDown(this), m_extremesValues(extremesValues), m_value(0), m_position(position), m_isSelect(false), m_isActive(false), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
	{
		if(position == Position::VERTICAL)
		{
			if(cursorSize <= 0 || cursorSize >= rect.width)
				cursorSize = rect.width;
			sf::Vector2f sizeMoveButton(rect.width, (100-pourcentageGlobalRectangle)*rect.height/200);

			m_globalRectangle.setRect(sf::FloatRect(m_pos.x, m_pos.y + sizeMoveButton.y, rect.width, rect.height - 2*sizeMoveButton.y));
			m_buttonDown.setRect(sf::FloatRect(m_pos.x, m_pos.y, sizeMoveButton.x, sizeMoveButton.y));
			m_buttonUp.setRect(sf::FloatRect(m_pos.x, m_pos.y + sizeMoveButton.y + m_globalRectangle.getSize().y, sizeMoveButton.x, sizeMoveButton.y));
		}

		else
		{
			if(cursorSize <= 0 || cursorSize >= rect.width)
				cursorSize = rect.height;
			sf::Vector2f sizeMoveButton((100-pourcentageGlobalRectangle)*rect.width/200, rect.height);

			m_globalRectangle.setRect(sf::FloatRect(rect.left + sizeMoveButton.x, rect.top, rect.width-2*sizeMoveButton.x, rect.height));
			m_buttonDown.setRect(sf::FloatRect(rect.left, rect.top, sizeMoveButton.x, sizeMoveButton.y));
			m_buttonUp.setRect(sf::FloatRect(rect.left + m_globalRectangle.getSize().x + sizeMoveButton.x, rect.top, sizeMoveButton.x, sizeMoveButton.y));
		}
	}

	Slide::Slide(Updatable *parent, float valueMin, float valueMax, const sf::FloatRect &rect, int cursorSize, const Position &position, int pourcentageGlobalRectangle) : Widget(parent, rect), m_extremesValues(sf::Vector2f(valueMin, valueMax)), m_value(0), m_position(position), m_isSelect(false), m_isActive(false), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
	{

	}

	Slide::Slide(Updatable *parent) : Widget(parent, sf::FloatRect(0, 0, 0, 0)), m_extremesValues(sf::Vector2f(0, 0)), m_position(Position::VERTICAL)
	{

	}

	Slide::Slide() : Widget(NULL, sf::FloatRect(0, 0, 0, 0)), m_extremesValues(sf::Vector2f(0, 0)), m_position(Position::VERTICAL)
	{

	}

	Slide::~Slide()
	{}

	void Slide::update(IRender &render)
	{

	}

	void Slide::setSize(float x, float y)
	{

	}

	void Slide::setPosition(float x, float y)
	{

	}

	void setPosition(const Position& position)
	{

	}

	void setExtremesValues(const sf::Vector2f &extremesValues)
	{

	}

	float Slide::getValue()
	{
		return m_value;
	}

	const sf::Vector2f& Slide::getExtremesValues()
	{
		return m_extremesValues;
	}
}
