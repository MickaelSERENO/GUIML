#ifndef DEF_FRAME
#define DEF_FRAME

#include "Label.h"
#include "Button.h"
#include "Render.h"

namespace guiml
{
	class Frame : public Render, public sf::RenderTexture
	{
	public:
		#include "SurchargeMethode.h"
		Frame(Updatable *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image(), const Label &title = Label(), const sf::Color &backgroundTitle = sf::Color(255, 255, 255, 255), bool drawButtonMoveFrame=true);

		void updateFocus();
		void update(IRender &render);
		virtual void draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default);

		void setTitle(const Label &title);
		void setSize(float x, float y);
		void setPosition(float x, float y);
		void setBackgroundTitle(const sf::Color &colorTitle);
		void setBackgroundTitle(const Image &image);
		void setRectMovingFrame(const sf::FloatRect &rect);
		void setBackgroundImage(const Image &backgroundImage);
		void setView(const sf::View &view);

		void setDrawButtonMoveFrame(bool drawButtonMoveFrame);
		void resetView();

		const Label& getLabelTitle() const;
		sf::FloatRect getRectMoveFrame() const;
		bool getDrawButtonMoveFrame() const;

		const PosText& positionTitle() const;
		bool isMoving();

		virtual sf::Vector2f getRenderViewPosition() const;
	protected:
		void testIsMoving();
		sf::Sprite m_spriteFrame;
		Button m_buttonMoveFrame;
		PosText m_posTitle;
		bool m_isMoving;
		bool m_hasAddChild;
		sf::Vector2f m_mousePos;
	};
}

#endif
