#include "Widget.h"

namespace guiml
{
	Widget::Widget(Widget *parent, const sf::IntRect &rect) : m_parent(NULL), m_isDrawing(true), m_pos(rect.left, rect.top), m_size(rect.width, rect.height), m_virtualPos(rect.left, rect.top), m_virtualSize(rect.width, rect.height), m_movingAllChild(false)
	{
		if(parent)
			parent->addChild(this);
	}

	Widget::Widget(const Widget &copy) : m_parent(NULL), m_isDrawing(copy.m_isDrawing), m_pos(copy.m_pos), m_size(copy.m_size), m_virtualPos(copy.m_virtualPos), m_virtualSize(copy.m_virtualSize), m_movingAllChild(copy.m_movingAllChild)
	{
		setParent(copy.m_parent);
	}

	Widget::~Widget()
	{
		if(m_parent)
			m_parent->removeChild(this);
		for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		{
			delete (*it); //delete all the child of the Widget
			it = m_child.erase(it);
		}
	}

	Widget& Widget::operator=(const Widget &copy)
	{
		if(&copy != this)
		{
			m_parent = NULL;
			m_isDrawing = copy.m_isDrawing;
			m_pos = copy.m_pos;
			m_size = copy.m_size;
			m_virtualPos = copy.m_virtualPos;
			m_virtualSize = copy.m_virtualSize;
			m_movingAllChild = copy.m_movingAllChild;
			for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			{
				delete *it;
				it = m_child.erase(it);
			}
		}

		return *this;
	}

	void Widget::addChild(Widget *child, int pos)
	{
		if(child->m_parent != this)
			child->setParent(this, pos);

		if(child != NULL && !isChild(child))
		{
			if(pos < 0 || pos >= m_child.size())
				m_child.push_back(child);

			else
			{
				std::list<Widget*>::iterator it;
				for(unsigned int i = 0; i < pos; ++i)
					it++;
				m_child.insert(it, child);
			}
		}
	}

	void Widget::setParent(Widget *parent, int pos)
	{
		if(m_parent)
			m_parent->removeChild(this);
		
		m_parent = parent;	
		if(parent)
			m_parent->Widget::addChild(this, pos);
	}

	void Widget::removeChild(Widget *child)
	{
		for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		{
			if(*it == child)
			{
				m_child.erase(it);
				return;
			}
		}
	}	

	void Widget::drawWidget(bool drawing)
	{
		m_isDrawing = drawing;
	}

	void Widget::drawAllChild(bool drawing)
	{
		for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			(*it)->drawWidget(drawing);
	}

	void Widget::update(std::list<sf::Drawable*> &drawables)
	{
		for(std::list<Widget*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
			if(*it)
				(*it)->update(drawables);
	}

	void Widget::setRect(const sf::IntRect &rect)
	{
		setPosition(rect.left, rect.top);
		setSize(rect.width, rect.height);
	}

	void Widget::setPosition(const sf::Vector2i &pos)
	{
		setPosition(pos.x, pos.y);
	}

	void Widget::setPosition(int x, int y)
	{
		if(m_movingAllChild)
			for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
				(*it)->move(x - m_virtualPos.x, y - m_virtualPos.y);

		EventManager *event = getEventManager();
		if(event)
		{
			sf::Vector2i defaultWindowSize = event->getDefaultWindowSize();
			if(defaultWindowSize.x != 0 && defaultWindowSize.y != 0)
			{
				sf::Vector2i newWindowSize = event->getNewWindowSize();
				m_pos = sf::Vector2i(x * newWindowSize.x/defaultWindowSize.x, y * newWindowSize.y / defaultWindowSize.y);
			}
			else
				m_pos = sf::Vector2i(x, y);
		}
		else
			m_pos = sf::Vector2i(x, y);
		m_virtualPos = sf::Vector2i(x, y);;
	}

	void Widget::setSize(int x, int y)
	{
		EventManager *event = getEventManager();
		if(event)
		{
			sf::Vector2i defaultWindowSize = event->getDefaultWindowSize();
			if(defaultWindowSize.x != 0 && defaultWindowSize.y != 0)
			{
				sf::Vector2i newWindowSize = event->getNewWindowSize();
				m_size = sf::Vector2i(x * newWindowSize.x/defaultWindowSize.x, y * newWindowSize.y / defaultWindowSize.y);
			}
		}
		else
			m_size = sf::Vector2i(x, y);
		m_virtualSize = sf::Vector2i(x, y);;
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

	void Widget::move(int x, int y)
	{
		setPosition(m_virtualPos.x + x, m_virtualPos.y + y);
	}

	void Widget::move(const sf::Vector2i &addPosition)
	{
		move(addPosition.x, addPosition.y);
	}

	void Widget::setSize(const sf::Vector2i &newSize)
	{
		setSize(newSize.x, newSize.y);	
	}

	void Widget::addSize(int x, int y)
	{
		setSize(m_virtualSize.x + x, m_virtualSize.y + y);
	}

	void Widget::addSize(const sf::Vector2i &addingSize)
	{
		addSize(addingSize.x, addingSize.y);
	}

	void Widget::moveAllChild(bool movingAllChild)
	{
		m_movingAllChild = movingAllChild;
		for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			(*it)->moveAllChild(movingAllChild);
	}

	bool Widget::getMovingAllChild() const
	{
		return m_movingAllChild;
	}

	EventManager* Widget::getEventManager() const
	{
		if(m_parent == NULL)
			return NULL;
		return m_parent->getEventManager();
	}

	bool Widget::isDrawing() const
	{
		return m_isDrawing;
	}

	bool Widget::hasParent() const
	{
		return m_parent;
	}

	bool Widget::isChild(const Widget *child)
	{
		bool isChild = false;

		for(std::list<Widget*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if((*it) == child)
			{
				isChild = true;
				break;
			}

		return isChild;
	}

	const sf::Vector2i& Widget::getPosition() const 
	{
		return m_pos;
	}

	const sf::Vector2i& Widget::getSize() const 
	{
		return m_size;
	}

	const sf::Vector2i& Widget::getVirtualPosition() const 
	{
		return m_virtualPos;
	}

	const sf::Vector2i& Widget::getVirtualSize() const 
	{
		return m_virtualSize;
	}

	sf::IntRect Widget::getRect()const 
	{
		return sf::IntRect(m_pos.x, m_pos.y, m_size.x, m_size.y);
	}
	
	sf::IntRect Widget::getVirtualRect() const
	{
		return sf::IntRect(m_virtualPos.x, m_virtualPos.y, m_virtualSize.x, m_virtualSize.y);
	}

	void Widget::resizeWidget(const sf::Vector2i& defaultWindowSize, const sf::Vector2i& newWindowSize)
	{
		m_size.x = m_virtualSize.x * newWindowSize.x / defaultWindowSize.x;
		m_pos.x = m_virtualPos.x * newWindowSize.x / defaultWindowSize.x;

		m_size.y = m_virtualSize.y * newWindowSize.y / defaultWindowSize.y;
		m_pos.y = m_virtualPos.y * newWindowSize.y / defaultWindowSize.y;

		for(std::list<Widget*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
			(*it)->resizeWidget(defaultWindowSize, newWindowSize);
	}

	Widget* Widget::copy() const
	{
		return new Widget(*this);
	}
}