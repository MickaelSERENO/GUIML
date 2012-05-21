#include "Label.h"

namespace guiml
{
	Label::Label(Widget *parent, const std::string &string, const sf::Vector2i &position, int characterSize) : Widget(parent, sf::IntRect(position.x, position.y, characterSize * string.size(), characterSize)), m_text(sf::String(string))
	{
		setRect(sf::IntRect(position.x, position.y, characterSize * string.size(), characterSize));
	}

	Label::Label(Widget *parent, const sf::String &string, const sf::Vector2i &position, int characterSize) : Widget(parent, sf::IntRect(position.x, position.y, characterSize * string.getSize(), characterSize)), m_text(string)
	{
		setRect(sf::IntRect(position.x, position.y, characterSize * string.getSize(), characterSize));
	}

	Label::Label(Widget *parent, const sf::Text &text, const sf::Vector2i &position, int characterSize) : Widget(parent, sf::IntRect(position.x, position.y, characterSize * text.getString().getSize(), characterSize)), m_text(text)
	{
		setRect(sf::IntRect(position.x, position.y, characterSize * text.getString().getSize(), characterSize));
	}

	Label::Label(Widget *parent) : Widget(parent)
	{}

	Label::Label() : Widget(NULL)
	{}

	Label::Label(const Label &copy) : Widget(copy), m_text(copy.m_text)
	{
	}

	Label& Label::operator=(const Label &copy)
	{
		if(this != &copy)
		{
			Widget::operator=(copy);
			m_text = copy.m_text;
		}
		return *this;
	}

	void Label::update(std::list<sf::Drawable*> &drawable)
	{
		if(m_isDrawing)
			drawable.push_back(&m_text);
		Widget::update(drawable);
	}

	void Label::lighten()
	{
		sf::Color pixel = m_text.getColor();

		float c = float(pixel.r)/255;
		pixel.r = 255*(3*c*c-2*c*c*c);
		c = float(pixel.g)/255;
		pixel.g = 255*(3*c*c-2*c*c*c);
		c = float(pixel.b)/255;
		pixel.b = 255*(3*c*c-2*c*c*c);
		
		m_text.setColor(pixel);
	}

	const sf::String &Label::getString() const
	{
		return m_text.getString();
	}

	const sf::Text &Label::getText() const
	{
		return m_text;
	}


	void Label::setOrigin(float x, float y)
	{
		m_text.setOrigin(x, y);
	}

	void Label::setOrigin(sf::Vector2f &pos)
	{
		setOrigin(pos.x, pos.y);
	}

	void Label::setDefaultOrigin()
	{
		setOrigin(m_text.getLocalBounds().left, m_text.getLocalBounds().top);
	}

	void Label::setOriginMiddle()
	{
		setOrigin(m_text.getLocalBounds().left + m_virtualSize.x / 2, m_text.getLocalBounds().top + m_virtualSize.y / 2);
	}

	void Label::setRightOrigin()
	{
		setOrigin(m_text.getLocalBounds().left + m_virtualSize.x, m_text.getLocalBounds().top + m_virtualSize.y);
	}

	void Label::rotate(float angle)
	{
		m_text.rotate(angle);
		setRect(sf::IntRect(m_text.getPosition().x, m_text.getPosition().y, m_text.getGlobalBounds().width, m_text.getGlobalBounds().height));
	}

	void Label::setStyle(sf::Uint32 style)
	{
		m_text.setStyle(style);
	}

	void Label::setRotation(float angle)
	{
		m_text.setRotation(angle);
		setRect(sf::IntRect(m_text.getPosition().x, m_text.getPosition().y, m_text.getGlobalBounds().width, m_text.getGlobalBounds().height));
	}

	void Label::setPosition(int x, int y)
	{
		Widget::setPosition(x, y);
		m_text.setPosition(x, y);
	}

	void Label::setFontText(const sf::Font &font)
	{
		m_text.setFont(font);	
	}

	void Label::setTextWidthSize(unsigned int size)
	{
		std::cout << "the size is " << size << std::endl;
		if(getString().getSize() != 0)
			setCharacterSize(size / getString().getSize());
	}	

	void Label::setCharacterSize(unsigned int size)
	{
		std::cout << "the characters is " << size << std::endl;
		m_text.setCharacterSize(size);
		Widget::setSize(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
	}

	void Label::setColor(const sf::Color &color)
	{
		m_text.setColor(color);
	}

	void Label::setSize(int x, int y)
	{
		m_text.setScale(x/m_text.getLocalBounds().width, y/m_text.getLocalBounds().height);
		Widget::setSize(m_text.getGlobalBounds().width, m_text.getGlobalBounds().height);
	}

	void Label::setLabel(const sf::Text &string)
	{
		m_text = string;
		setRect(getVirtualRect());
	}

	void Label::setLabel(const sf::String &string)
	{
		m_text.setString(string);
		setRect(getVirtualRect());
	}

	void Label::setLabel(const std::string &string)
	{
		setLabel(sf::String(string));
		setRect(getVirtualRect());
	}

	Widget* Label::copy() const
	{
		return new Label(*this);
	}
}
