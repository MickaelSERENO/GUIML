#include "Widget.h"

namespace guiml
{
	class Slide : public Widget
	{
	public:
		Slide(Widget *parent, const sf::FloatRect &rect);
		Slide(const Slide &copy);

		void Update(std::list<sf::Drawable*> &drawable);

		void SetSize(float x, float y);
		void SetPosition(float x, float y);

		unsigned int GetValue();
	}
}
