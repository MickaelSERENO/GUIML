#include "Slide.h"

namespace guiml
{
	Slide::Slide(Widget *parent, const sf::Vector2f &extremesValues, const sf::FloatRect &rect, const Position& position, int pourcentageGlobalRectangle) : Widget(parent, rect), m_buttonValue(this), m_buttonUp(this), m_buttonDown(this), m_extremesValues(extremesValues), m_value(0), m_position(position), m_isSelect(false), m_isActive(false), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
	{
		if(position == Position::VERTICAL)
		{
			sf::Vector2f sizeMoveButtons(rect.width, (100-pourcentageGlobalRectangle)*rect.height/200);

			m_globalRectangle.setSize(sf::Vector2f(rect.width - 2*sizeMoveButtons.x, rect.height - 2*sizeMoveButtons.y));
			m_globalRectangle.setPosition(m_pos.x, m_pos.y + sizeMoveButtons.y);

			m_buttonUp.setRect(sf::FloatRect(m_pos.x, m_pos.y, sizeMoveButtons.x, sizeMoveButtons.y));
			m_buttonDown.setRect(sf::FloatRect(m_pos.x, m_pos.y + sizeMoveButtons.y + m_globalRectangle.getSize().y, sizeMoveButtons.x, sizeMoveButtons.y));
		}

		else
		{
		}
	}

	Slide::Slide(Widget *parent, float valueMin, float valueMax, const sf::FloatRect &rect, const Position &position, int pourcentageGlobalRectangle) : Widget(parent, rect), m_extremesValues(sf::Vector2f(valueMin, valueMax)), m_value(0), m_position(position), m_isSelect(false), m_isActive(false), m_pourcentageGlobalRectangle(pourcentageGlobalRectangle)
	{

	}

	Slide::Slide(Widget *parent) : Widget(parent, sf::FloatRect(0, 0, 0, 0)), m_extremesValues(sf::Vector2f(0, 0)), m_position(Position::VERTICAL)
	{

	}

	Slide::Slide() : Widget(NULL, sf::FloatRect(0, 0, 0, 0)), m_extremesValues(sf::Vector2f(0, 0)), m_position(Position::VERTICAL)
	{

	}

	Slide::~Slide()
	{}

	void Slide::update(std::list<sf::Drawable*> &drawable)
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
