#include "Frame.h"

namespace guiml
{
	Frame::Frame(Widget *parent, const sf::IntRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage, const Label &title, const sf::Color &backgroundTitle) : Render(parent, rect, backgroundColor, backgroundImage), sf::RenderTexture(), m_backgroundTitle(sf::Vector2f(rect.width, title.getSize().y)), m_title(title), m_buttonMoveFrame(NULL, guiml::Label(), guiml::Image(), sf::IntRect(0, 0, rect.width, title.getSize().y)), m_posTitle(PosText::CENTER), m_isMoving(false), m_hasAddChild(false)
	{
		m_movingAllChild = false;

		m_title.setParent(this);
		m_title.setOriginMiddle();
		m_title.setPosition(m_virtualSize.x / 2, 0);
		m_title.setColor(sf::Color::White);

		m_buttonMoveFrame.setParent(this);

		m_backgroundTitle.setFillColor(backgroundTitle);
		m_backgroundTitle.setPosition(getPosition().x, getPosition().y);
		create(m_virtualSize.x, m_virtualSize.y);

		resetView();
	}

	void Frame::update(std::list<sf::Drawable*> &drawable)
	{
		if(m_isDrawing)
		{
			if(isMoving())
			{
				sf::Vector2i defaultWindowSize = getEventManager()->getDefaultWindowSize();
				sf::Vector2i newWindowSize = getEventManager()->getNewWindowSize();

				sf::Vector2i oldMousePos = getEventManager()->getOldMousePosition();
				sf::Vector2i mousePos = getEventManager()->getMousePosition();
				move(mousePos.x - oldMousePos.x, mousePos.y - oldMousePos.y);
			}

			for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
				(*it)->move(m_virtualPos.x, m_virtualPos.y);

			clear(m_backgroundColor);
			std::list<sf::Drawable*> drawableForFrame;
			Widget::update(drawableForFrame);
			show(drawableForFrame);
			drawable.push_back(&m_spriteFrame);

			for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
				(*it)->move(-m_virtualPos.x, -m_virtualPos.y);
		}
		
		else
			clear(sf::Color(0, 0, 0, 255));
	}

	void Frame::show(std::list<sf::Drawable*> &drawable)
	{
		draw(m_backgroundTitle);
		for(std::list<sf::Drawable*>::iterator it = drawable.begin(); it != drawable.end(); ++it)
			draw(*(*it));
		display();
		m_spriteFrame.setTexture(getTexture());
		m_spriteFrame.setPosition(sf::Vector2f(m_virtualPos.x, m_virtualPos.y));
	}

	void Frame::setTitle(const Label &title)
	{
		m_title = title;
		m_title.setParent(this);
		m_buttonMoveFrame.setSize(m_buttonMoveFrame.getSize().x, m_title.getSize().y);
		setTitlePos(m_posTitle);
		m_backgroundTitle.setSize(sf::Vector2f(m_virtualSize.x, title.getSize().y));
		setTitle(title.getString().toAnsiString());
	}

	void Frame::setTitle(const std::string &title)
	{
		setTitle(Label(NULL, title));
		Render::setTitle(title);
	}

	void Frame::setView(const sf::View &view)
	{
		Render::setView(view);
		sf::RenderTexture::setView(view);
		if(&view != &m_renderView)
			moveView(m_virtualPos.x, m_virtualPos.y);
	}
		
	void Frame::resetView()
	{
		setView(sf::RenderTexture::getDefaultView());
	}

	void Frame::setSize(int x, int y)
	{
		create(x, y);
		Widget::setSize(x, y);
		m_backgroundTitle.setSize(sf::Vector2f(m_virtualSize.x, m_backgroundTitle.getSize().y));
	}

	void Frame::setPosition(int x, int y)
	{
		moveView(x - m_virtualPos.x, y - m_virtualPos.y);
		Widget::setPosition(x, y);
		m_backgroundTitle.setPosition(m_virtualPos.x, m_virtualPos.y);
	}

	void Frame::setBackgroundTitle(const sf::Color &colorTitle)
	{
		m_backgroundTitle.setFillColor(colorTitle);
	}

	void Frame::setRectMovingFrame(const sf::IntRect &rect)
	{
		m_buttonMoveFrame.setRect(rect);
	}

	void Frame::setTitlePos(const PosText &posTitle)
	{
		m_posTitle = posTitle;
		if(m_posTitle == PosText::CENTER)
		{
			m_title.setOriginMiddle();
			m_title.setPosition(m_virtualPos.x + m_virtualSize.x / 2, m_virtualPos.y);
		}

		else if(m_posTitle == PosText::RIGHT)
		{
			m_title.setRightOrigin();
			m_title.setPosition(m_virtualPos.x + m_virtualSize.x, m_virtualPos.y);
		}

		else if(m_posTitle==PosText::LEFT)
		{
			m_title.setDefaultOrigin();
			m_title.setPosition(m_virtualPos);
		}
	}

	void Frame::setBackgroundImage(const Image &backgroundImage)
	{
		Render::setBackgroundImage(backgroundImage);
		m_backgroundImage.setRect(sf::IntRect(m_virtualPos.x, m_virtualPos.y - m_backgroundTitle.getSize().y, m_virtualSize.x, m_virtualSize.y));
	}

	const Label& Frame::getLabelTitle() const
	{
		return m_title;
	}

	sf::IntRect Frame::getRectMoveFrame() const
	{
		return m_buttonMoveFrame.getVirtualRect();
	}

	const PosText& Frame::positionTitle() const
	{
		return m_posTitle;
	}

	bool Frame::isMoving()
	{
		if(!m_isMoving)
			m_isMoving = m_buttonMoveFrame.isActived();
		else if(!(getEventManager()->getPressedKey(m_buttonMoveFrame.getKeyboardWhoActived()) || getEventManager()->getMouseClicked(m_buttonMoveFrame.getClickMouseWhoActived())))
			m_isMoving = false;
		return m_isMoving;
	}

	sf::FloatRect Frame::getViewport() const
	{
		sf::FloatRect rect = m_renderView.getViewport();
		rect.left -= m_virtualPos.x;
		rect.top -= m_virtualPos.y;

		return rect;
	}
}
