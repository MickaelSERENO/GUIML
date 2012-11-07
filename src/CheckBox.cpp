#include "CheckBox.h"

namespace guiml
{
	CheckBox::CheckBox(Updatable *parent, const sf::FloatRect &rect) : Widget(parent, rect), Active(), m_rectangle(sf::Vector2f(rect.width, rect.height)), m_line1(sf::Lines, 2), m_line2(sf::Lines, 2), m_howActivedKeyboard(sf::Keyboard::End), m_howActivedClickMouse(sf::Mouse::Left)
	{
		m_rectangle.setPosition(rect.left, rect.top);
		setOutlineColorRectangle(sf::Color::White);
		setOutlineThickness(2);
		setCrossColor(sf::Color::Black);

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

	void CheckBox::update(IRender &render)
	{
		Active::update();
		Widget::update(render);
	}

	void CheckBox::draw(IRender &render)
	{
		render.draw(m_rectangle);
		if(m_isActive)
		{
			render.draw(m_line1);
			render.draw(m_line2);
		}
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

	void CheckBox::setCrossColor(const sf::Color &color)
	{
		m_line1[0].color=color;
		m_line1[1].color=color;
		m_line2[0].color=color;
		m_line2[1].color=color;
	}

	void CheckBox::setOutlineColorRectangle(const sf::Color &color)
	{
		m_rectangle.setOutlineColor(color);
		setSize(m_virtualSize);
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
		if(Widget::widgetMouseSelect == this || m_isSelectCopy)
			m_isSelect = true;

		else
			m_isSelect = false;

		return m_isSelect;
	}

	bool CheckBox::updateActivation()
	{
		if(m_isSelect && m_event && (m_event->getOneMouseClicked(m_howActivedClickMouse) || m_event->getOnePressedKey(m_howActivedKeyboard)))
			m_isActive = !m_isActive; 
		
		return m_isActive;
	}

	Widget* CheckBox::copy() const
	{
		return new CheckBox(*this);
	}
}
