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
		Frame(Widget *parent, const sf::IntRect &rect, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image(), const Label &title = Label(), const sf::Color &backgroundTitle = sf::Color(255, 255, 255, 255), bool drawButtonMoveFrame=true);

		void update(std::list<sf::Drawable*> &drawable);
		void show(std::list<sf::Drawable*> &drawable);

		void setTitle(const Label &title);
		void setTitle(const std::string &title);
		void setSize(int x, int y);
		void setPosition(int x, int y);
		void setBackgroundTitle(const sf::Color &colorTitle);
		void setBackgroundTitle(const Image &image);
		void setRectMovingFrame(const sf::IntRect &rect);
		void setTitlePos(const PosText &posTitle);
		void setBackgroundImage(const Image &backgroundImage);
		void setView(const sf::View &view);

		void setDrawButtonMoveFrame(bool drawButtonMoveFrame);
		void resetView();

		const Label& getLabelTitle() const;
		sf::IntRect getRectMoveFrame() const;
		sf::FloatRect getViewport() const;
		bool getDrawButtonMoveFrame() const;

		const PosText& positionTitle() const;
		bool isMoving();

		virtual void resizeWidget(const sf::Vector2i& defaultWindowSize, const sf::Vector2i& newWindowSize);
	protected:
		void testIsMoving();
		sf::Sprite m_spriteFrame;
		guiml::Label m_title;
		Button m_buttonMoveFrame;
		PosText m_posTitle;
		bool m_isMoving;
		bool m_hasAddChild;
		sf::Vector2i m_mousePos;
	};
}

#endif
