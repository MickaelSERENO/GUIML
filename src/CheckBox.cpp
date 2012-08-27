#include "CheckBox.h"

namespace guiml
{
	CheckBox::CheckBox(Updatable *parent, const sf::FloatRect &rect) : Widget(parent, rect), Active(), m_rectangle(sf::Vector2f(rect.width, rect.height)), m_line1(sf::Lines, 2), m_line2(sf::Lines, 2), m_howActivedKeyboard(sf::Keyboard::End), m_howActivedClickMouse(sf::Mouse::Left)
	{
		m_rectangle.setPosition(rect.left, rect.top);
		setFillColorRectangle(sf::Color(0, 0, 0, 0));
		setOutlineColorRectangle(sf::Color(255, 255, 255));
		setOutlineThickness(2);

		m_line1[0].position = sf::Vector2f(rect.left, rect.top);
		m_line1[1].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);

		m_line2[0].position = sf::Vector2f(rect.left + rect.width, rect.top);
		m_line2[1].position = sf::Vector2f(rect.left, rect.top + rect.height);
	}

	CheckBox::CheckBox(const CheckBox &copy) : Widget(copy), Active(), m_rectangle(copy.m_rectangle), m_line1(copy.m_line1), m_line2(copy.m_line2), m_howActivedKeyboard(copy.m_howActivedKeyboard), m_howActivedClickMouse(copy.m_howActivedClickMouse){}

	CheckBox& CheckBox::operator=(const CheckBox &copy)
	{
		if(this != &copy)
		{
			Widget::operator=(copy);
			Active::operator=(copy);
			m_rectangle = copy.m_rectangle;
			m_line1 = copy.m_line1;
			m_line2 = copy.m_line2;
			m_howActivedKeyboard = copy.m_howActivedKeyboard;
			m_howActivedClickMouse = copy.m_howActivedClickMouse;
		}
		return *this;
	}

	void CheckBox::update(std::list<sf::Drawable*> &drawable)
	{
		if(m_isDrawing)
		{
			drawable.push_back(&m_rectangle);
			Active::update();
			if(m_isActive)
			{
				drawable.push_back(&m_line1);
				drawable.push_back(&m_line2);
			}
		}
		Widget::update(drawable);
	}

	void CheckBox::setSize(float x, float y)
	{
		m_rectangle.setSize(sf::Vector2f(x, y));
		m_line1[1].position = sf::Vector2f(m_virtualPos.x + x, m_virtualPos.y + y);
		
		m_line2[0].position = sf::Vector2f(m_virtualPos.x + x, m_virtualPos.y);
		m_line2[1].position = sf::Vector2f(m_virtualPos.x, y + m_virtualPos.y);
		Widget::setSize(x, y);
	}

	void CheckBox::setPosition(float x, float y)
	{
		m_rectangle.setPosition(x, y);

		m_line1[0].position = sf::Vector2f(x, y);
		m_line1[1].position = sf::Vector2f(x + m_virtualSize.x, y + m_virtualSize.y);

		m_line2[0].position = sf::Vector2f(x + m_virtualSize.x, y);
		m_line2[1].position = sf::Vector2f(x, m_virtualSize.y + y);

		Widget::setPosition(x, y);
	}

	void CheckBox::setKeyboardWhoActived(const sf::Keyboard::Key &key)
	{
		m_howActivedKeyboard = key;
	}

	void CheckBox::setClickMouseWhoActived(const sf::Mouse::Button &mouseButton)
	{
		m_howActivedClickMouse = mouseButton;
	}

	void CheckBox::setOutlineColorRectangle(const sf::Color &color)
	{
		m_rectangle.setOutlineColor(color);
	}

	void CheckBox::setFillColorRectangle(const sf::Color &color)
	{
		m_rectangle.setFillColor(color);
	}

	void CheckBox::setColorCross(const sf::Color &color)
	{
		m_line1[0].color = color;
		m_line1[1].color = color;

		m_line2[0].color = color;
		m_line2[1].color = color;
	}

	void CheckBox::setOutlineThickness(float x)
	{
		m_rectangle.setOutlineThickness(x);
	}

	bool CheckBox::updateSelection()
	{
		if(getEventManager()->isMouseInRect(getVirtualRect()) || m_isSelectCopy)
			m_isSelect = true;

		else
			m_isSelect = false;

		return m_isSelect;
	}

	bool CheckBox::updateActivation()
	{
		if(m_isSelect && (getEventManager()->getOneMouseClicked(m_howActivedClickMouse) || getEventManager()->getOnePressedKey(m_howActivedKeyboard)))
		{
			if(m_isActive)
				m_isActive = false; 
			else
				m_isActive = true;
		}

		return m_isActive;
	}

	Widget* CheckBox::copy() const
	{
		return new CheckBox(*this);
	}
}
