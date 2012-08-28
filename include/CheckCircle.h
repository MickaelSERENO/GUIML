#ifndef DEF_CHECKCIRCLE
#define DEF_CHACKCIRCLE

#include "Widget.h"
#include "Active.h"

namespace guiml
{
	class CheckCircle : public Widget, public Active
	{
		public:
			#include "SurchargeMethode.h"
			CheckCircle(Updatable *parent, const sf::FloatRect &rect);
			CheckCircle(const CheckCircle &copy);

			virtual void update(std::list<sf::Drawable*> &drawable);

			void setSize(float x, float y);
			void setPosition(float x, float y);

			void setKeyboardWhoActived(const sf::Keyboard &key);
			void setClickMouseWhoActived(const sf::Mouse::Button &mouseButton);

			void setOutlineColorRectangle(const sf::Color &color);
			void setFillColorRectangle(const sf::Color &color);
			void setOutlineThickness(float x);
			void setColorCross(const sf::Color &color);

			bool updateSelection();
			bool updateActivation();

			CheckCircle& operator=(const CheckCircle &copy);
		private:
			sf::CircleShape m_outline;
			sf::CircleShape m_check;

			unsigned int m_howActivedKeyboard;
			unsigned int m_howActivedClickMouse;
	};
}

#endif
