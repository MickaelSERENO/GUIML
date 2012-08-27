#ifndef DEF_CASEBOX
#define DEF_CASEBOX

#include "Widget.h"
#include "Active.h"

namespace guiml
{
	class CheckBox : public Widget, public Active
	{
	public:
		#include "SurchargeMethode.h"
		CheckBox(Updatable* parent, const sf::FloatRect &rect);
		CheckBox(const CheckBox &copy);

		virtual void update(std::list<sf::Drawable*> &drawable);

		void setSize(float x, float y);
		void setPosition(float x, float y);
	
		void setKeyboardWhoActived(const sf::Keyboard::Key &key);
		void setClickMouseWhoActived(const sf::Mouse::Button &mouseButton);

		void setOutlineColorRectangle(const sf::Color &color);
		void setFillColorRectangle(const sf::Color &color);
		void setOutlineThickness(float x);

		void setColorCross(const sf::Color &color);
		
		bool updateSelection();
		bool updateActivation();

		CheckBox& operator=(const CheckBox &copy);
		Widget* copy() const;
	private:
		sf::RectangleShape m_rectangle;
		sf::VertexArray m_line1;
		sf::VertexArray m_line2;

		unsigned int m_howActivedKeyboard;
		unsigned int m_howActivedClickMouse;
	};
}

#endif
