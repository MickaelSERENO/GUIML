#ifndef DEF_FRAME
#define DEF_FRAME

#include "Label.h"
#include "Button.h"
#include "Render.h"

namespace guiml
{
	enum PosText
	{
		CENTER,
		RIGHT,
		LEFT
	};

	class Frame : public Render, public sf::RenderTexture
	{
	public:
		#include "SurchargeMethode.h"
		Frame(Updatable *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image(), const Label &title = Label(), const sf::Color &backgroundTitle = sf::Color(255, 255, 255, 255), bool drawButtonMoveFrame=true);

		void update(IRender &render);
		virtual void draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default);

		void setTitle(const Label &title);
		void setSize(float x, float y);
		void setPosition(float x, float y);
		void setBackgroundTitle(const sf::Color &colorTitle);
		void setBackgroundTitle(const Image &image);
		void setRectMovingFrame(const sf::FloatRect &rect);
		void setTitlePos(const PosText &posTitle);
		void setBackgroundImage(const Image &backgroundImage);
		void setView(const sf::View &view);

		void setDrawButtonMoveFrame(bool drawButtonMoveFrame);
		void resetView();

		const Label& getLabelTitle() const;
		sf::FloatRect getRectMoveFrame() const;
		sf::FloatRect getViewport() const;
		bool getDrawButtonMoveFrame() const;

		const PosText& positionTitle() const;
		bool isMoving();
	protected:
		void testIsMoving();
		sf::Sprite m_spriteFrame;
		guiml::Label m_title;
		Button m_buttonMoveFrame;
		PosText m_posTitle;
		bool m_isMoving;
		bool m_hasAddChild;
		sf::Vector2f m_mousePos;
	};
}

#endif
