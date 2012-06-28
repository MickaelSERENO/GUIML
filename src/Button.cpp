#include "Button.h"

namespace guiml
{
	Button::Button(Widget *parent, const Label &text, const sf::FloatRect &rect) : Widget(parent, rect), m_hasBackground(false), m_hasLabel(true), m_background(NULL), m_text(text), m_backgroundLighten(NULL), m_textLighten(text), m_isSelect(false), m_isSelectCopy(false), m_howActivedKeyboard(sf::Keyboard::Escape), m_howActivedClickMouse(sf::Mouse::Left), m_isActived(false)
	{
		m_textLighten.lighten();
		m_currentBackground = &m_background;
		m_currentLabel = &m_text;

		if(rect == sf::FloatRect(0, 0, 0, 0))
			setRect(m_text.getVirtualRect());
		else
			setRect(rect);
		drawWidget(true);
	}

	Button::Button(Widget *parent, const Image &image, const sf::FloatRect &rect) : Widget(parent, rect), m_hasBackground(true), m_hasLabel(false), m_background(image), m_text(NULL), m_backgroundLighten(image), m_textLighten(NULL) ,m_isSelect(false), m_isSelectCopy(false), m_howActivedKeyboard(sf::Keyboard::Escape), m_howActivedClickMouse(sf::Mouse::Left), m_isActived(false)
	{
		m_backgroundLighten.lighten();
		m_currentBackground = &m_background;
		m_currentLabel = &m_text;
		if(rect == sf::FloatRect(0, 0, 0, 0))
			setRect(m_background.getVirtualRect());
		else
			setRect(rect);
		drawWidget(true);
	}

	Button::Button(Widget *parent, const Label &text, const Image &image, const sf::FloatRect &rect) : Widget(parent, rect), m_hasBackground(true), m_hasLabel(true), m_background(image), m_text(text), m_backgroundLighten(image), m_textLighten(text), m_isSelect(false), m_isSelectCopy(false), m_howActivedKeyboard(sf::Keyboard::Escape), m_howActivedClickMouse(sf::Mouse::Left), m_isActived(false)
	{
		m_textLighten.lighten();
		m_backgroundLighten.lighten();
		m_currentBackground = &m_background;
		m_currentLabel = &m_text;
		if(rect == sf::FloatRect(0, 0, 0, 0))
			setRect(m_background.getVirtualRect());
		else
			setRect(rect);
		drawWidget(true);
	}

	Button::Button(const Button &copy) : Widget(copy), m_hasBackground(copy.m_hasBackground), m_hasLabel(copy.m_hasLabel), m_background(copy.m_background), m_text(copy.m_text), m_backgroundLighten(copy.m_backgroundLighten), m_textLighten(copy.m_textLighten), m_isSelect(copy.m_isSelect), m_isSelectCopy(copy.m_isSelectCopy), m_howActivedKeyboard(copy.m_howActivedKeyboard), m_howActivedClickMouse(copy.m_howActivedClickMouse), m_isActived(copy.m_isActived)
	{
		m_currentBackground = &m_background;
		m_currentLabel = &m_text;
		drawWidget(copy.m_isDrawing);
	}

	Button::Button(Widget *parent) : Widget(parent)
	{}

	Button::Button() : Widget (NULL), m_hasBackground(false), m_hasLabel(false), m_currentBackground(NULL), m_currentLabel(NULL), m_isSelect(false), m_isSelectCopy(false), m_howActivedKeyboard(sf::Keyboard::Escape), m_howActivedClickMouse(sf::Mouse::Left), m_isActived(false)
	{}

	Button& Button::operator=(const Button &copy)
	{
		if(this != &copy)
		{
			Widget::operator=(copy);
			m_hasBackground = copy.m_hasBackground;
			m_hasLabel = copy.m_hasLabel;
			m_background = copy.m_background;
			m_text = copy.m_text;
			m_textLighten = copy.m_textLighten;
			if(copy.m_currentBackground == &copy.m_background)
				m_currentBackground = &m_background;
			else
				m_currentBackground = &m_backgroundLighten;
	
			if(copy.m_currentLabel == &copy.m_text)
				m_currentLabel = &m_text;
			else
				m_currentLabel = &m_textLighten;
	
			m_isSelect = copy.m_isSelect;
			m_isSelectCopy = copy.m_isSelectCopy;
			m_howActivedClickMouse = copy.m_howActivedClickMouse;
			m_howActivedKeyboard = copy.m_howActivedKeyboard;
			m_isActived = copy.m_isActived;
		}

		return *this;
	}

	//................Escape of Constructor..............
	
	void Button::update(std::list<sf::Drawable*> &drawable)
	{
		if(m_isDrawing)
		{
			cursorInButton();
			if(m_isSelect && (getEventManager()->getOneMouseClicked(m_howActivedClickMouse) || getEventManager()->getOnePressedKey(m_howActivedKeyboard)))
				m_isActived = true;
			else
				m_isActived = false;
		}

		else
		{
			m_isSelect = false;
			m_isActived = false;
		}
		Widget::update(drawable);
	}

	void Button::centerLabel()
	{
		if(m_hasLabel)
		{
			m_text.setOriginMiddle();
			m_text.setPosition(m_virtualPos.x + m_virtualSize.x / 2, m_virtualPos.y + m_virtualSize.y / 2);
			m_textLighten.setOriginMiddle();
			m_textLighten.setPosition(m_virtualPos.x + m_virtualSize.x / 2, m_virtualPos.y + m_virtualSize.y / 2);
		}
	}

	bool Button::cursorInButton()
	{
		if(getEventManager()->isMouseInRect(getRect()) || m_isSelectCopy)
		{
			m_isSelect = true;
			lightUpDrawable();
			return true;
		}

		else
		{
			m_isSelect = false;
			lightUpDrawable(false);
			return false;
		}
	}

	void Button::lightUpDrawable(bool lighten)
	{
		if(lighten)
		{
			if(m_hasBackground)
			{
				m_currentBackground = &m_backgroundLighten;
				m_backgroundLighten.setParent(this);
				m_background.setParent(NULL);
			}

			if(m_hasLabel)
			{
				m_currentLabel = &m_textLighten;	
				m_textLighten.setParent(this);
				m_text.setParent(NULL);
			}
		}
		else
		{
			if(m_hasBackground)
			{
				m_currentBackground = &m_background;
				m_background.setParent(this);
				m_backgroundLighten.setParent(NULL);
			}

			if(m_hasLabel)
			{
				m_currentLabel = &m_text;
				m_text.setParent(this);
				m_textLighten.setParent(NULL);
			}
		}
	}

	void Button::drawWidget(bool drawing)
	{
		m_background.drawWidget(drawing);
		m_backgroundLighten.drawWidget(drawing);
		m_text.drawWidget(drawing);
		m_textLighten.drawWidget(drawing);
	}

	void Button::setPosition(float posx, float posy)
	{
		if(m_hasBackground)
		{
			m_background.setPosition(posx, posy);
			m_backgroundLighten.setPosition(posx, posy);
		}

		Widget::setPosition(posx, posy);
		centerLabel();
	}

	void Button::setSize(float sizex, float sizey)
	{
		if(m_hasBackground)
		{
			m_background.setSize(sizex, sizey);
			m_backgroundLighten.setSize(sizex, sizey);
		}

		if(m_hasLabel)
		{
			m_text.setTextWidthSize(sizex);
			m_textLighten.setTextWidthSize(sizex);
		}
		Widget::setSize(sizex, sizey);
		centerLabel();
	}

	void Button::setBackground(const Image &image)
	{
		m_background = image;
		m_backgroundLighten = image;
		m_backgroundLighten.lighten();
		m_hasBackground = true;
		setRect(getVirtualRect());
	}

	void Button::setLabel(const Label &string)
	{
		m_text = string;
		m_textLighten = string;
		m_textLighten.lighten();
		m_hasLabel = true;
		setRect(getVirtualRect());
	}

	void Button::setKeyboardWhoActived(const sf::Keyboard::Key &key)
	{
		m_howActivedKeyboard = key;
	}

	void Button::setClickMouseWhoActived(const sf::Mouse::Button &mouseButton)
	{
		m_howActivedClickMouse = mouseButton;
	}

	void Button::setCharacterSize(unsigned int newsize)
	{
		if(m_hasLabel)
		{
			m_text.setCharacterSize(newsize);
			m_textLighten.setCharacterSize(newsize);
		}
		centerLabel();
	}

	void Button::selectIt(bool select)
	{
		m_isSelect = m_isSelectCopy = select;
	}

	void Button::activedIt(bool actived)
	{
		m_isActived = actived;
	}

	const Label* Button::getLabel() const
	{
		return m_currentLabel;
	}

	const Image* Button::getBackground() const
	{
		return m_currentBackground;
	}

	const unsigned int Button::getKeyboardWhoActived() const
	{
		return m_howActivedKeyboard;
	}

	const unsigned int Button::getClickMouseWhoActived() const
	{
		return m_howActivedClickMouse;
	}

	bool Button::hasImage() const
	{
		return m_hasBackground;
	}

	bool Button::hasLabel() const 
	{
		return m_hasLabel;
	}

	bool Button::isSelect() const 
	{
		return m_isSelect;
	}

	bool Button::isActived() const 
	{
		return m_isActived;
	}

	Widget* Button::copy() const
	{
		return new Button(*this);
	}
}
