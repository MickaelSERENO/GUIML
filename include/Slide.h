#include "Widget.h"
#include "Button.h"

namespace guiml
{
	enum Position
	{
		HORIZONTAL,
		VERTICAL
	};

	class Slide : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		Slide(Widget *parent, const sf::Vector2f& extremesValues, const sf::IntRect &rect, const Position& position = Position::VERTICAL);
		Slide(Widget *parent, float valueMin, float valueMax, const sf::IntRect &rect, const Position& position = Position::VERTICAL);
		Slide(Widget *parent);
		Slide();
		Slide(const Slide &copy);

		virtual ~Slide();

		void update(std::list<sf::Drawable*> &drawable);

		void setSize(float x, float y);
		void setPosition(float x, float y);

		void setPosition(const Position &position);

		void setExtremesValues(const sf::Vector2i &extremesValues);

		int getValue();
		const sf::Vector2i getExtremesValues();

	private:
		sf::RectangleShape m_rectangleValue;
		sf::RectangleShape m_rectangleGlobal;
		Button m_buttonUp;
		Button m_buttonDown;

		sf::Vector2f m_extremesValues;
		Position m_position;
	};
}
