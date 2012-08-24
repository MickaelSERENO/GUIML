#ifndef DEF_BUTTON
#define DEF_BUTTON

#include "Widget.h"
#include "Image.h"
#include "Label.h"

namespace guiml
{
	class Button : public Widget
	{
	public:	
		#include "SurchargeMethode.h"
		//-----------------------------------All constructors for various parameters-------------------------------------//
		Button(Updatable *parent, const Label &text, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Button(Updatable *parent, const Image &image, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Button(Updatable *parent, const Label &text, const Image &image, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Button(Updatable *parent, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Button();
		Button(const Button &copy);
		//-------------------------------------------End of constructors--------------------------------------------//

		virtual void update(std::list<sf::Drawable*> &drawable);
		bool cursorInButton();
		void lightUpDrawable(bool lighten = true);

		//------------------------------------------Mutateurs---------------------------------------------------//
		virtual void drawWidget(bool drawing);
		void setPosition(float posx, float posy);
		void setSize(float sizex, float sizey);
		void setBackground(const Image &image);
		void setLabel(const Label &string);
		void selectIt(bool select);
		void activedIt(bool actived);

		void setKeyboardWhoActived(const sf::Keyboard::Key &key);
		void setClickMouseWhoActived(const sf::Mouse::Button &mouseButton);
		void setCharacterSize(unsigned int newsize);

		//-----------------------------------------End of Mutateurs--------------------------------------------//


		const Label* getLabel() const;
		const Image* getBackground() const;
		const unsigned int getKeyboardWhoActived() const;
		const unsigned int getClickMouseWhoActived() const;

		bool hasImage()const ;
		bool hasLabel() const ;
		bool isSelect() const ;	
		bool isActived() const ;

		Button& operator=(const Button &copy);
		Widget* copy() const;

	protected:
		void centerLabel(); //Center the Label with regard to the background
		bool m_hasBackground;
		bool m_hasLabel;

		Image m_background;
		Label m_text;
		Image m_backgroundLighten;
		Label m_textLighten;
		Image *m_currentBackground;
		Label *m_currentLabel;
		bool m_isSelect;
		bool m_isSelectCopy;

		unsigned int m_howActivedKeyboard;
		unsigned int m_howActivedClickMouse;
		bool m_isActived;
	};
}

#endif 
