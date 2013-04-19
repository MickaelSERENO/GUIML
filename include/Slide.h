#include "Widget.h"
#include "Button.h"

namespace guiml
{
	enum Orientation
	{
		HORIZONTAL,
		VERTICAL
	};

	enum SlideStyle
	{
		LINEAIRE,
		BUTTON
	};

	class Slide : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		Slide(Updatable *parent, const sf::Vector2f& extremesValues, const sf::FloatRect &globalRect, int cursorSize=-1, const Orientation& position = Orientation::VERTICAL, int pourcentageGlobalRectangle=100);
		Slide(Updatable *parent, float valueMin, float valueMax, const sf::FloatRect &rect, int cursorSize = -1, const Orientation& position = Orientation::VERTICAL, int pourcentageGlobalRectangle=100);
		Slide(Updatable *parent);
		Slide();

		Slide(const Slide &copy);
		Slide& operator=(const Slide &copy);

		virtual ~Slide();

		void update(IRender &render);

		void setSize(float x, float y);
		void setOrientation(float x, float y);

		void setOrientation(const Orientation &position);

		void setExtremesValues(const sf::Vector2f &extremesValues);

		float getValue();
		const sf::Vector2f& getExtremesValues();

	private:
		Button m_globalRectangle;

		Button m_cursor;
		Button m_buttonUp;
		Button m_buttonDown;

		sf::Vector2f m_extremesValues;
		float m_value;
		Orientation m_position;

		bool m_isSelect;
		bool m_isActive;

		int m_pourcentageGlobalRectangle;
	};
}
