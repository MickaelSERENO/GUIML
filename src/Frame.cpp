#include "Frame.h"

namespace guiml
{
	Frame::Frame(Updatable *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor, const Image &backgroundImage, const Label &title, const sf::Color &backgroundTitle, bool drawButtonMoveFrame) : Render(parent, rect, backgroundColor, backgroundImage), sf::RenderTexture(), m_buttonMoveFrame(NULL, guiml::Label(), guiml::Image(), sf::FloatRect(0, 0, rect.width, title.getSize().y)), m_posTitle(PosText::CENTER), m_isMoving(false), m_hasAddChild(false)
	{
		setRect(getVirtualRect());
		m_movingAllChild = false;

		sf::Texture texture;
		sf::Sprite sprite(texture, sf::IntRect(0, 0, rect.width, title.getSize().y));
		sprite.setColor(backgroundTitle);

		m_buttonMoveFrame.setParent(this);
		m_buttonMoveFrame.setBackground(Image(NULL, sprite));
		m_buttonMoveFrame.setLabel(title);

		create(m_virtualSize.x, m_virtualSize.y);
		resetView();
		m_spriteFrame.setTexture(getTexture(), true);
		if(!drawButtonMoveFrame)
			m_buttonMoveFrame.drawWidget(false);
	}

	void Frame::updateFocus()
	{
		Updatable::updateFocus();
	}

	void Frame::update(IRender &render)
	{
		if(m_isDrawing)
		{
			if(m_event && isMoving())
			{
				sf::Vector2f newMousePosition = m_event->getMousePosition();
				sf::Vector2f multiplicateMousePos = m_event->getMultiplicateMousePos();
				setPosition((newMousePosition.x/multiplicateMousePos.x)-m_mousePos.x, (newMousePosition.y/multiplicateMousePos.y)-m_mousePos.y);
			}

			std::list<Widget*> child = extractFromUpdatableChild<Widget>();
			for(std::list<Widget*>::iterator it = child.begin(); it != child.end(); ++it)
				if(*it)
					(*it)->move(m_virtualPos.x-getViewPosition().x, m_virtualPos.y-getViewPosition().y); 

			clear(m_backgroundColor);
			Updatable::updateFocus();
			Updatable::update(*this);

			display();
			render.draw(m_spriteFrame);

			for(std::list<Widget*>::iterator it = child.begin(); it != child.end(); ++it)
				if(*it)
					(*it)->move(-m_virtualPos.x+getViewPosition().x, -m_virtualPos.y+getViewPosition().y); 
		}
	}

	void Frame::draw(const sf::Drawable &drawable, const sf::RenderStates &states)
	{
		sf::RenderTexture::draw(drawable, states);
	}

	void Frame::setTitle(const Label &title)
	{
		m_buttonMoveFrame.setLabel(title);
		m_buttonMoveFrame.setSize(m_virtualSize.x, title.getVirtualSize().y);
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

	void Frame::setSize(float x, float y)
	{
		create(x, y);
		Widget::setSize(x, y);
		m_buttonMoveFrame.setSize(sf::Vector2f(m_virtualSize.x, m_buttonMoveFrame.getVirtualSize().y));
	}

	void Frame::setPosition(float x, float y)
	{
		moveView(x-m_virtualPos.x, y-m_virtualPos.y);
		Widget::setPosition(x, y);
		m_spriteFrame.setPosition(m_virtualPos);
	}

	void Frame::setBackgroundTitle(const sf::Color &colorTitle)
	{
		sf::Texture texture;
		sf::FloatRect rect = m_buttonMoveFrame.getRect();
		sf::Sprite sprite(texture, sf::IntRect(rect.left, rect.top, rect.width, rect.height));
		sprite.setColor(colorTitle);
		m_buttonMoveFrame.setBackground(Image(NULL, sprite));
	}

	void Frame::setBackgroundTitle(const Image& image)
	{
		m_buttonMoveFrame.setBackground(image);
	}

	void Frame::setRectMovingFrame(const sf::FloatRect &rect)
	{
		m_buttonMoveFrame.setRect(rect);
	}

	void Frame::setBackgroundImage(const Image &backgroundImage)
	{
		Render::setBackgroundImage(backgroundImage);
		m_backgroundImage.setRect(sf::FloatRect(m_virtualPos.x, m_virtualPos.y - m_buttonMoveFrame.getSize().y, m_virtualSize.x, m_virtualSize.y));
	}

	void Frame::setDrawButtonMoveFrame(bool drawButtonMoveFrame)
	{
		m_buttonMoveFrame.drawWidget(drawButtonMoveFrame);
	}

	sf::FloatRect Frame::getRectMoveFrame() const
	{
		return m_buttonMoveFrame.getVirtualRect();
	}

	bool Frame::getDrawButtonMoveFrame() const
	{
		return m_buttonMoveFrame.isDrawing();
	}

	const PosText& Frame::positionTitle() const
	{
		return m_posTitle;
	}

	sf::Vector2f Frame::getViewPosition() const
	{
		sf::Vector2f initial = Render::getViewPosition();
		initial.x -= m_virtualPos.x;
		initial.y -= m_virtualPos.y;
		return initial;
	}

	bool Frame::isMoving()
	{
		if(!m_isMoving && m_event)
		{
			m_isMoving = m_buttonMoveFrame.isActive();
			m_mousePos = m_event->getMousePosition();
			sf::Vector2f multiplicateMousePos = m_event->getMultiplicateMousePos();

			m_mousePos.x /= multiplicateMousePos.x;
			m_mousePos.x -= m_virtualPos.x;	
			m_mousePos.y /= multiplicateMousePos.y;
			m_mousePos.y -= m_virtualPos.y;
		}
		else if(!(m_event && (m_event->getPressedKey(m_buttonMoveFrame.getKeyboardWhoActived()) || m_event->getMouseClicked(m_buttonMoveFrame.getClickMouseWhoActived()))))
			m_isMoving = false;
		return m_isMoving;
	}

	bool Frame::isInView(const sf::FloatRect& rect) const
	{
		sf::FloatRect viewRect = getViewRect();
		viewRect.left += m_virtualPos.x;
		viewRect.top += m_virtualPos.y;

		return rectCollision(rect, viewRect);
	}
}
