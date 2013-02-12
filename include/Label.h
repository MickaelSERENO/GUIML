#ifndef DEF_LABEL
#define DEF_LABEL

#include "Widget.h"

namespace guiml
{
	enum PosText
	{
		CENTER,
		RIGHT,
		LEFT
	};

	class Label : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		Label(Updatable *parent, const std::string &string, const sf::Font &font, const sf::Vector2f &position = sf::Vector2f(0, 0), int characterSize = 12);
		Label(Updatable *parent, const sf::String &string, const sf::Font &font, const sf::Vector2f &position = sf::Vector2f(0, 0), int characterSize = 12);
		Label(Updatable *parent, const sf::Text &text, const sf::Vector2f &position = sf::Vector2f(0, 0), int characterSize = 12);
		Label(Updatable *parent);
		Label();
		Label(const Label &copy);

		virtual void updateFocus();
		virtual void draw(IRender &render);
		void lighten();

		const sf::String &getString() const;
		const sf::Text &getText() const;
		bool getUpdateFocus() const;
		virtual sf::FloatRect getRect() const;
		virtual sf::FloatRect getVirtualRect() const;

		void setOrigin(float x, float y);
		void setOrigin(sf::Vector2f &pos);
		void setOriginMiddle();
		void setDefaultOrigin();
		void setRightOrigin();
		void rotate(float angle);
		void setStyle(sf::Uint32 style);
		void setRotation(float angle);

		void setFontText(const sf::Font &font);
		void setTextWidthSize(unsigned int size);
		void setTextHeightSize(unsigned int size);
		void setCharacterSize(unsigned int size);
		void setColor(const sf::Color &color);
		
		void setLabel(const sf::Text &string);
		void setLabel(const sf::String &string);
		void setLabel(const std::string &string);

		void setPosition(float x, float y);
		void setSize(float x, float y);
		void setUpdateFocus(bool updateFocus);
		Label& operator=(const Label &copy);
		Widget* copy() const;
	private:
		sf::Text m_text;
		bool m_updateFocus;
	};
}

#endif
