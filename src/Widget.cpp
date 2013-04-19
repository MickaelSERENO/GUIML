#include "Widget.h"

RessourcesManager<sf::Texture*> guiml::Widget::fileLoading;
bool guiml::Widget::focusIsCheck = false;
guiml::Widget* guiml::Widget::widgetMouseSelect = NULL;

namespace guiml
{
	Widget::Widget(Updatable *parent, const sf::FloatRect &rect) : Updatable(parent), m_isDrawing(true), m_isStaticToView(false), m_origin(0, 0), m_pos(rect.left, rect.top), m_size(rect.width, rect.height), m_virtualPos(rect.left, rect.top), m_virtualSize(rect.width, rect.height), m_posOnScreen(m_virtualPos.x - getRenderViewPosition().x, m_virtualPos.y - getRenderViewPosition().y), m_posSaved(m_virtualPos), m_scale(1,1), m_movingAllChild(false), m_focus(true), m_posOrigin(TopLeft)
	{}

	Widget::Widget(const Widget &copy) : Updatable(copy), m_isDrawing(copy.m_isDrawing), m_isStaticToView(copy.m_isStaticToView), m_origin(copy.m_origin), m_pos(copy.m_pos), m_size(copy.m_size), m_virtualPos(copy.m_virtualPos), m_virtualSize(copy.m_virtualSize), m_posOnScreen(m_virtualPos), m_posSaved(copy.m_posSaved), m_scale(copy.m_scale), m_movingAllChild(copy.m_movingAllChild), m_focus(copy.m_focus), m_posOrigin(copy.m_posOrigin)
	{}

	Widget& Widget::operator=(const Widget &copy)
	{
		if(&copy != this)
		{
			Updatable::operator=(copy);
			m_isDrawing = copy.m_isDrawing;
			m_origin = copy.m_origin;
			m_pos = copy.m_pos;
			m_size = copy.m_size;
			m_virtualPos = copy.m_virtualPos;
			m_virtualSize = copy.m_virtualSize;
			m_movingAllChild = copy.m_movingAllChild;
			m_posOnScreen = copy.m_posOnScreen;
			m_isStaticToView = copy.m_isStaticToView;
			m_posSaved = copy.m_posSaved;
			m_scale = copy.m_scale;
			m_focus=copy.m_focus;
			m_posOrigin = copy.m_posOrigin;
		}

		return *this;
	}

	void Widget::updateFocus()
	{
		if(m_focus)
		{
			sf::Vector2f renderParentViewPosition = getRenderViewPosition();
			getPosOnScreen();

			if(m_isDrawing && m_event && m_event->isMouseInRect(getRectOnScreen()))
			{
				Updatable::focusIsCheck = true;
				Widget::widgetMouseSelect=this;
				return;
			}

			Updatable::updateFocus();
		}
	}

	void Widget::update(IRender &render)
	{
		if(m_changeWindow)
			setRect(sf::FloatRect(m_virtualPos, m_virtualSize));

		if(m_isStaticToView)
		{
			sf::Vector2f posInit = m_posSaved;
			setPosition(m_posSaved.x + render.getViewPosition().x, m_posSaved.y + render.getViewPosition().y);
			m_posSaved = posInit;
		}

		if(m_isDrawing && render.isInView(getVirtualRect()))
			draw(render);

		Updatable::update(render);
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

	void Widget::setUpdateFocus(bool focus)
	{
		m_focus = focus;
	}

	void Widget::setStaticToView(bool dontMove)
	{
		m_isStaticToView=dontMove;
	}

	void Widget::setOrigin(const sf::Vector2f& origin)
	{
		setOrigin(origin.x, origin.y);
	}

	void Widget::setOrigin(float x, float y)
	{
		m_origin=sf::Vector2f(x, y);
		setPosition(m_virtualPos.x+x, m_virtualPos.y+y, false);
	}

	void Widget::setPosOrigin(const Position& position)
	{
		switch(position)
		{
			case TopRight:
				m_origin=sf::Vector2f(m_size.x, 0);
				break;
			case TopLeft:
				m_origin=sf::Vector2f(0, 0);
				break;
			case Center:
				m_origin=sf::Vector2f(m_size.x/2, m_size.y/2);
				break;
			case BottomRight:
				m_origin=sf::Vector2f(m_size.x, m_size.y);
				break;
			case BottomLeft:
				m_origin=sf::Vector2f(0, m_size.y);
				break;
		}
		setPosition(m_virtualPos);
		m_posOrigin=position;
	}

	void Widget::setPosition(const sf::Vector2f &pos, bool withOrigin)
	{
		setPosition(pos.x, pos.y);
	}

	void Widget::setPosition(float x, float y, bool withOrigin)
	{
/*  	if(m_movingAllChild)
			for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
				if(Widget* child = dynamic_cast<Widget*>(*it))
					child->move(x - m_virtualPos.x, y - m_virtualPos.y);
*/

		if(m_event)
		{
			sf::Vector2f defaultWindowSize = m_event->getDefaultWindowSize();
			if(defaultWindowSize.x != 0 && defaultWindowSize.y != 0)
			{
				sf::Vector2f newWindowSize = m_event->getNewWindowSize();
				if(withOrigin)
					m_pos = sf::Vector2f((-m_origin.x + x) * newWindowSize.x/defaultWindowSize.x, (-m_origin.y + y) * newWindowSize.y / defaultWindowSize.y);
				else
					m_pos = sf::Vector2f(x * newWindowSize.x/defaultWindowSize.x, y * newWindowSize.y / defaultWindowSize.y);

			}

			else
			{
				if(withOrigin)
					m_pos = sf::Vector2f(x-m_origin.x, y-m_origin.y);
				else
					m_pos = sf::Vector2f(x, y);
			}
		}
		else
		{
			if(withOrigin)
				m_pos = sf::Vector2f(x-m_origin.x, y-m_origin.y);
			else
				m_pos = sf::Vector2f(x, y);
		}
		if(withOrigin)
			m_virtualPos = sf::Vector2f(x-m_origin.x, y-m_origin.y);
		else
			m_virtualPos = sf::Vector2f(x, y);

		m_posSaved = m_virtualPos;
	}

	void Widget::setPositionOnScreen(const sf::Vector2f &pos, bool withOrigin)
	{
		setPositionOnScreen(pos.x, pos.y, withOrigin);
	}

	void Widget::setPositionOnScreen(float x, float y, bool withOrigin)
	{
		setPosition(x-getRenderViewPosition().x, y-getRenderViewPosition().y, withOrigin);
		m_posOnScreen = sf::Vector2f(x, y);
	}
	
	void Widget::setSize(float x, float y)
	{
		m_scale=(1,1);
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
		setPosOrigin(m_posOrigin);
	}

	void Widget::setRect(const sf::FloatRect &rect)
	{
		setSize(rect.width, rect.height);
		setPosition(rect.left, rect.top, false);
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
		m_scale = sf::Vector2f(x*m_scale.x, y*m_scale.y);
	}

	void Widget::setScale(const sf::Vector2f &scale)
	{
		setScale(scale.x, scale.y);
	}

	void Widget::setScale(float x, float y)
	{
		setSize(m_size*x/m_scale.x, m_size*y/m_scale.y);
		m_scale = sf::Vector2f(x,y);
	}

	void Widget::move(float x, float y)
	{
		setPosition(m_virtualPos.x + x, m_virtualPos.y + y, false);
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

	const sf::Vector2f& Widget::getOrigin() const
	{
		return m_origin;
	}

	Position Widget::getPosOrigin() const
	{
		return m_posOrigin;
	}

	bool Widget::getUpdateFocus() const
	{
		return m_focus;
	}

	sf::Vector2f Widget::getPosition(bool withOrigin) const 
	{
		if(withOrigin==false)
			return m_pos;
		if(m_pos.x == 0 && m_pos.y == 0)
			return m_origin; 
		else if(m_pos.x == 0)
			return sf::Vector2f(m_origin.x, m_pos.y/m_virtualPos.y*(m_virtualPos.y+m_origin.y));
		else if(m_pos.y==0)
			return sf::Vector2f(m_pos.x/m_virtualPos.x*(m_virtualPos.y+m_origin.y), +m_origin.y);
		else
			return sf::Vector2f(m_pos.x/m_virtualPos.x*(m_virtualPos.y+m_origin.y), m_pos.y/m_virtualPos.y*(m_virtualPos.y+m_origin.y));
	}

	const sf::Vector2f& Widget::getSize() const 
	{
		return m_size;
	}

	sf::Vector2f Widget::getVirtualPosition(bool withOrigin) const 
	{
		if(withOrigin==false)
			return m_virtualPos;
		else
			return sf::Vector2f(m_virtualPos.x +m_origin.x, m_virtualPos.y + m_origin.y);
	}

	sf::Vector2f Widget::getPosOnScreen(bool withOrigin)
	{
		sf::Vector2f renderParentViewPosition = getRenderViewPosition();
		sf::Vector2f pos = getPosition(withOrigin);
		if(m_event)
		{
			sf::Vector2f defaultWindowSize = m_event->getDefaultWindowSize();
			if(defaultWindowSize.x != 0 && defaultWindowSize.y != 0)
			{
				sf::Vector2f newWindowSize = m_event->getNewWindowSize();
				renderParentViewPosition = sf::Vector2f(renderParentViewPosition.x * newWindowSize.x/defaultWindowSize.x, renderParentViewPosition.y * newWindowSize.y / defaultWindowSize.y);
			}
		}
		m_posOnScreen = sf::Vector2f(pos.x - renderParentViewPosition.x, pos.y - renderParentViewPosition.y);

		return m_posOnScreen;
	}

	sf::Vector2f Widget::getVirtualPosOnScreen(bool withOrigin)
	{
		sf::Vector2f renderParentViewPosition = getRenderViewPosition();
		getPosOnScreen(withOrigin);
		sf::Vector2f virtualPos = getVirtualPosition(withOrigin);
		return sf::Vector2f(virtualPos.x - renderParentViewPosition.x, virtualPos.y - renderParentViewPosition.y);
	}

	const sf::Vector2f& Widget::getVirtualSize() const 
	{
		return m_virtualSize;
	}

	const sf::Vector2f& Widget::getScale() const
	{
		return m_scale;
	}

	sf::FloatRect Widget::getRect()const 
	{
		return sf::FloatRect(m_pos, m_size);
	}
	
	sf::FloatRect Widget::getVirtualRect() const
	{
		return sf::FloatRect(m_virtualPos, m_virtualSize);
	}

	sf::FloatRect Widget::getRectOnScreen()
	{
		return sf::FloatRect(getPosOnScreen(false), m_size);
	}

	sf::FloatRect Widget::getVirtualRectOnScreen()
	{
		return sf::FloatRect(getVirtualPosOnScreen(false), m_virtualSize);
	}

	sf::Vector2f Widget::getRenderViewPosition() const
	{
		if(m_parent)
			return m_parent->getRenderViewPosition();
		else
			return sf::Vector2f(0, 0);
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
