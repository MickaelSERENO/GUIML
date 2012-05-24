#include "Slide.h"

namespace guiml
{
	Slide::Slide(Widget *parent, const sf::Vector2f &extremesValues, const sf::IntRect &rect, const Position& position) : Widget(parent, rect), m_extremesValues(extremesValues), m_position(position)
	{

	}

	Slide::Slide(Widget *parent, float valueMin, float valueMax, const sf::IntRect &rect, const Position &position) : Widget(parent, rect), m_extremesValues(sf::Vector2f(valueMin, valueMax)), m_position(position)
	{

	}

	Slide::Slide(Widget *parent) : Widget(parent, sf::IntRect(0, 0, 0, 0)), m_extremesValues(sf::Vector2f(0, 0)), m_position(Position::VERTICAL)
	{

	}

	Slide::Slide() : Widget(NULL, sf::IntRect(0, 0, 0, 0)), m_extremesValues(sf::Vector2f(0, 0)), m_position(Position::VERTICAL)
	{

	}

	Slide::~Slide()
	{}

	void Slide::update(std::list<sf::Drawable*> &drawable)
	{

	}
}
