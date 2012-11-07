#include "Widget.h"

RessourcesManager<sf::Texture*> guiml::Widget::fileLoading;
bool guiml::Widget::focusIsCheck = false;
guiml::Widget* guiml::Widget::widgetMouseSelect = NULL;

namespace guiml
{
	Widget::Widget(Updatable *parent, const sf::FloatRect &rect) : Updatable(parent), m_isDrawing(true), m_isStaticToView(true), m_pos(rect.left, rect.top), m_size(rect.width, rect.height), m_virtualPos(rect.left, rect.top), m_virtualSize(rect.width, rect.height), m_movingAllChild(false)
	{}

	Widget::Widget(const Widget &copy) : Updatable(copy), m_isDrawing(copy.m_isDrawing), m_isStaticToView(true), m_pos(copy.m_pos), m_size(copy.m_size), m_virtualPos(copy.m_virtualPos), m_virtualSize(copy.m_virtualSize), m_movingAllChild(copy.m_movingAllChild)
	{}

	Widget& Widget::operator=(const Widget &copy)
	{
		if(&copy != this)
		{
			Updatable::operator=(copy);
			m_isDrawing = copy.m_isDrawing;
			m_pos = copy.m_pos;
			m_size = copy.m_size;
			m_virtualPos = copy.m_virtualPos;
			m_virtualSize = copy.m_virtualSize;
			m_movingAllChild = copy.m_movingAllChild;
		}

		return *this;
	}

	void Widget::updateFocus()
	{
		if(m_isDrawing && m_event && m_event->isMouseInRect(getRect()))
			Widget::widgetMouseSelect=this;
	}

	void Widget::update(IRender &render)
	{
		if(m_changeWindow)
			setRect(getVirtualRect());

//		if(m_isStaticToView)
//			setPosition(m_virtualPos.x + render.getViewPosition().x - render.getView().getSize().x/2, m_virtualPos.y + render.getViewPosition().y - render.getView().getSize().y/2); 
		if(m_isDrawing && render.isInView(getVirtualRect()))
			draw(render);

		Updatable::update(render);
		m_changeWindow = false;
	}

	void Widget::draw(IRender &render)
	{}

	void Widget::drawWidget(bool drawing)
	{
		m_isDrawing = drawing;
	}

	void Widget::drawAllChild(bool drawing)
	{
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if(Widget* child = dynamic_cast<Widget*>(*it))
				child->drawWidget(drawing);
	}

	void Widget::setStaticToView(bool dontMove)
	{
		m_isStaticToView=dontMove;
	}

	void Widget::setPosition(const sf::Vector2f &pos)
	{
		setPosition(pos.x, pos.y);
	}

	void Widget::setPosition(float x, float y)
	{
		if(m_movingAllChild)
			for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
				if(Widget* child = dynamic_cast<Widget*>(*it))
					child->move(x - m_virtualPos.x, y - m_virtualPos.y);

		if(m_event)
		{
			sf::Vector2f defaultWindowSize = m_event->getDefaultWindowSize();
			if(defaultWindowSize.x != 0 && defaultWindowSize.y != 0)
			{
				sf::Vector2f newWindowSize = m_event->getNewWindowSize();
				m_pos = sf::Vector2f(x * newWindowSize.x/defaultWindowSize.x, y * newWindowSize.y / defaultWindowSize.y);
			}
			else
				m_pos = sf::Vector2f(x, y);
		}
		else
			m_pos = sf::Vector2f(x, y);
		m_virtualPos = sf::Vector2f(x, y);;
	}

	void Widget::setSize(float x, float y)
	{
		if(m_event)
		{
			sf::Vector2f defaultWindowSize = m_event->getDefaultWindowSize();
			if(defaultWindowSize.x != 0 && defaultWindowSize.y != 0)
			{
				sf::Vector2f newWindowSize = m_event->getNewWindowSize();
				m_size = sf::Vector2f(x * newWindowSize.x/defaultWindowSize.x, y * newWindowSize.y / defaultWindowSize.y);
			}
			else
				m_size = sf::Vector2f(x, y);
		}
		else
			m_size = sf::Vector2f(x, y);
		m_virtualSize = sf::Vector2f(x, y);;
	}

	void Widget::setRect(const sf::FloatRect &rect)
	{
		setSize(rect.width, rect.height);
		setPosition(rect.left, rect.top);
	}

	void Widget::scale(float x)
	{
		scale(x, x);
	}

	void Widget::scale(const sf::Vector2f &scaling)
	{
		scale(scaling.x, scaling.y);
	}

	void Widget::scale(float x, float y)
	{
		setSize(x * m_size.x, y * m_size.y);
	}

	void Widget::move(float x, float y)
	{
		setPosition(m_virtualPos.x + x, m_virtualPos.y + y);
	}

	void Widget::move(const sf::Vector2f &addPosition)
	{
		move(addPosition.x, addPosition.y);
	}

	void Widget::setSize(const sf::Vector2f &newSize)
	{
		setSize(newSize.x, newSize.y);	
	}

	void Widget::addSize(float x, float y)
	{
		setSize(m_virtualSize.x + x, m_virtualSize.y + y);
	}

	void Widget::addSize(const sf::Vector2f &addingSize)
	{
		addSize(addingSize.x, addingSize.y);
	}

	void Widget::moveAllChild(bool movingAllChild)
	{
		m_movingAllChild = movingAllChild;
		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if(Widget* child = dynamic_cast<Widget*>(*it))
				child->moveAllChild(movingAllChild);
	}

	bool Widget::getMovingAllChild() const
	{
		return m_movingAllChild;
	}

	bool Widget::isDrawing() const
	{
		return m_isDrawing;
	}

	bool Widget::isStaticToView() const
	{
		return m_isStaticToView;
	}

	const sf::Vector2f& Widget::getPosition() const 
	{
		return m_pos;
	}

	const sf::Vector2f& Widget::getSize() const 
	{
		return m_size;
	}

	const sf::Vector2f& Widget::getVirtualPosition() const 
	{
		return m_virtualPos;
	}

	const sf::Vector2f& Widget::getVirtualSize() const 
	{
		return m_virtualSize;
	}

	sf::FloatRect Widget::getRect()const 
	{
		return sf::FloatRect(m_pos.x, m_pos.y, m_size.x, m_size.y);
	}
	
	sf::FloatRect Widget::getVirtualRect() const
	{
		return sf::FloatRect(m_virtualPos.x, m_virtualPos.y, m_virtualSize.x, m_virtualSize.y);
	}

	void Widget::resizeWidget(const sf::Vector2f& defaultWindowSize, const sf::Vector2f& newWindowSize)
	{
		m_size.x = m_virtualSize.x * newWindowSize.x / defaultWindowSize.x;
		m_pos.x = m_virtualPos.x * newWindowSize.x / defaultWindowSize.x;

		m_size.y = m_virtualSize.y * newWindowSize.y / defaultWindowSize.y;
		m_pos.y = m_virtualPos.y * newWindowSize.y / defaultWindowSize.y;

		for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
			if(Widget* child = dynamic_cast<Widget*>(*it))
				child->resizeWidget(defaultWindowSize, newWindowSize);
	}

	Widget* Widget::copy() const
	{
		return new Widget(*this);
	}

	const Widget* Widget::getFocus()
	{
		return Widget::widgetMouseSelect;
	}
}
