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
		Slide(Widget *parent, const sf::Vector2f& extremesValues, const sf::FloatRect &rect, const Position& position = Position::VERTICAL, int pourcentageGlobalRectangle=97);
		Slide(Widget *parent, float valueMin, float valueMax, const sf::FloatRect &rect, const Position& position = Position::VERTICAL, int pourcentageGlobalRectangle=97);
		Slide(Widget *parent);
		Slide();

		Slide(const Slide &copy);
		Slide& operator=(const Slide &copy);

		virtual ~Slide();

		void update(std::list<sf::Drawable*> &drawable);

		void setSize(float x, float y);
		void setPosition(float x, float y);

		void setPosition(const Position &position);

		void setExtremesValues(const sf::Vector2f &extremesValues);

		float getValue();
		const sf::Vector2f& getExtremesValues();

	private:
		sf::RectangleShape m_globalRectangle;
		Button m_buttonValue;
		Button m_buttonUp;
		Button m_buttonDown;

		sf::Vector2f m_extremesValues;
		float m_value;
		Position m_position;

		bool m_isSelect;
		bool m_isActive;

		int m_pourcentageGlobalRectangle;
	};
}
