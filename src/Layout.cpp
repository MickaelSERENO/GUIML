#include "Layout.h"

namespace guiml
{
	Layout::Layout(Widget *parent, const sf::IntRect &rect, const std::vector<std::vector<Widget*> > &widgets, const sf::Vector2i &distance) : Widget(parent, rect), m_distance(distance), m_scale(1, 1)
	{

		unsigned int i, j;

		//Add all widgets in the Layout
		for(i = 0; i < widgets.size(); ++i)
		{
			m_widgetList.push_back(std::vector<Widget*>());
			m_sizeWidget.push_back(std::vector<sf::Vector2i>());
			for(j = 0; j < widgets[i].size(); ++j)
			{
				if(widgets[i][j])
				{
					m_widgetList[i].push_back(widgets[i][j]->copy());
				}
				else
					m_widgetList[i].push_back(new Widget(NULL));
				m_widgetList[i][j]->setParent(this);
				m_sizeWidget[i].push_back(sf::Vector2i(1, 1));
			}
		}
		sf::Vector2i addSize(0, 0);
		sf::Vector2i addPos(0, 0);

		setRect(getRect());
	}

	Layout::Layout(const Layout& copy) : Widget(copy), m_distance(copy.m_distance)
	{
		for(unsigned int i = 0; i < copy.m_widgetList.size() ; ++i)
		{
			m_widgetList.push_back(std::vector<Widget*>());
			for(unsigned int j = 0; j < copy.m_widgetList[i].size(); ++j)
			{
				if(m_widgetList[i][j])
					m_widgetList[i].push_back(copy.m_widgetList[i][j]->copy());
				else
					m_widgetList[i].push_back(NULL);
			}
		}
	}

	Layout& Layout::operator=(const Layout &copy)
	{
		if(this != &copy)
		{
			Widget::operator=(copy);
			m_distance = copy.m_distance;	
			for(unsigned int i = 0; i < copy.m_widgetList.size() ; ++i)
			{
				m_widgetList.push_back(std::vector<Widget*>());
				for(unsigned int j = 0; j < copy.m_widgetList[i].size(); ++j)
				{
					if(m_widgetList[i][j])
						m_widgetList[i].push_back(copy.m_widgetList[i][j]->copy());
					else
						m_widgetList[i].push_back(NULL);
				}
			}
		}
		return *this;
	}	

	Layout::~Layout()
	{
		for(unsigned int i=0; i < getSizeGrid().x; ++i)
		{
			for(unsigned int j=0; j < getSizeGrid().y; ++j)
			{
				if(m_widgetList[i][j])
					delete m_widgetList[i][j];
				m_widgetList[i][j]=NULL;
			}
		}
	}

	void Layout::update(std::list<sf::Drawable*> &drawable)
	{
		Widget::update(drawable);
	}

	void Layout::setSize(int x, int y)
	{
		sf::Vector2i addSize(-(getRealDistance().x-getRealDistance().x/getSizeGrid().x), -(getRealDistance().y - getRealDistance().y/getSizeGrid().y)); //We need to remove a part of the widget's size for correspond at m_distance.

		for(unsigned int i = 0; i < getSizeGrid().x; ++i)
		{
			for(unsigned int j = 0; j < getSizeGrid().y; ++j)
			{
				if(m_widgetList[i][j])
					m_widgetList[i][j]->setSize(addSize.x + x/getSizeGrid().x*m_sizeWidget[i][j].x + m_distance.x * (m_sizeWidget[i][j].x - 1), addSize.y + y/getSizeGrid().y*m_sizeWidget[i][j].y + m_distance.y * (m_sizeWidget[i][j].y) - 1);		
			}
		}

		setPosition(getPosition());
	}

	void Layout::setPosition(int x, int y)
	{
		for(unsigned int i=0; i < getSizeGrid().x; ++i)
			for(unsigned int j=0; j < getSizeGrid().y; ++j)
			{
				if(m_widgetList[i][j])
				{
					if(i > 0 && j > 0)
						m_widgetList[i][j]->setPosition(x+ i*m_virtualSize.x/getSizeGrid().x + m_distance.x, y + j*m_virtualSize.y/getSizeGrid().y + m_distance.y);
					else if(i == 0 && j > 0)
						m_widgetList[i][j]->setPosition(x+ i*m_virtualSize.x/getSizeGrid().x, y + j*m_virtualSize.y/getSizeGrid().y + m_distance.y);
					else if(i > 0 && j == 0)
						m_widgetList[i][j]->setPosition(x+ i*m_virtualSize.x/getSizeGrid().x + m_distance.x, y + j*m_virtualSize.y/getSizeGrid().y);
					else if(i == 0 && j == 0)
						m_widgetList[i][j]->setPosition(x+ i*m_virtualSize.x/getSizeGrid().x, y + j*m_virtualSize.y/getSizeGrid().y);
				}
			}
		Widget::setPosition(x, y);
	}

	void Layout::setDistance(unsigned int x, unsigned int y)
	{
		m_distance = sf::Vector2i(x, y);
		setSize(getSize());
	}

	void Layout::setDistance(const sf::Vector2i &distance)
	{
		setDistance(distance.x, distance.y);
	}

	void Layout::addWidget(const Widget *widget, const sf::Vector2i &pos, const sf::Vector2i &nbCase)
	{		
		std::vector<std::vector<Widget*>> widgets;
		std::vector<std::vector<sf::Vector2i>> widgetSize;
		unsigned int addNbCase = 0;
		unsigned int l = 0;

		if(pos.x + nbCase.x > getSizeGrid().x)
			addNbCase = pos.x + nbCase.x - getSizeGrid().x;

		for(unsigned int i = 0; i < getSizeGrid().x + addNbCase; ++i)
		{
			widgets.push_back(std::vector<Widget*>());
			widgetSize.push_back(std::vector<sf::Vector2i>());
			for(unsigned int j = 0; j < getSizeGrid().y + nbCase.y; ++j)
			{
				if(sf::Vector2i(i, j) == pos)
				{
					widgets[i].push_back(widget->copy());
					widgets[i][j]->setParent(this);
					widgets[i][j]->scale(sf::Vector2f(nbCase.x, nbCase.y));
					widgetSize[i].push_back(nbCase);
				}

				else if(i >= pos.x && i < pos.x + nbCase.x && j >= pos.y && j < pos.y + nbCase.y)
				{
					widgets[i].push_back(NULL);
					widgetSize[i].push_back(sf::Vector2i(0, 0));
				}
				
				else if(i < getSizeGrid().x && l < getSizeGrid().y)
				{
					widgets[i].push_back(m_widgetList[i][l]);
					widgetSize[i].push_back(sf::Vector2i(m_sizeWidget[i][l]));
					l++;
				}

				else
				{
					widgets[i].push_back(new Widget(NULL));
					widgets[i][j]->setParent(this);
					widgetSize[i].push_back(sf::Vector2i(0, 0));
					l++;
				}
			}
			l = 0;
		}
		m_widgetList = widgets;
		m_sizeWidget = widgetSize;

		setRect(getRect());
	}

	void Layout::removeChild(const sf::Vector2i &pos)
	{
		sf::Vector2i bigWidgetPos = hasBigWidget(pos);
		if(bigWidgetPos != sf::Vector2i(-1, -1))
		{
			for(unsigned int i = bigWidgetPos.x; i < bigWidgetPos.x + m_sizeWidget[pos.x][pos.y].x; ++i)
				for(unsigned int j = bigWidgetPos.y; i < bigWidgetPos.y + m_sizeWidget[pos.x][pos.y].y; ++j)
				{
					delete m_widgetList[i][j];
					m_widgetList[i][j] = new Widget(NULL);
				}
		}

		else if(pos.x < getSizeGrid().x && pos.y < getSizeGrid().y)
		{
			delete m_widgetList[pos.x][pos.y];
			m_widgetList[pos.x][pos.y] = new Widget(NULL);
		}
	}

	bool Layout::isEmpty() const
	{
		return m_widgetList.empty();
	}

	sf::Vector2i Layout::getSizeGrid() const
	{
		if(m_sizeWidget.empty())
			return sf::Vector2i(0, 0);
		
		return sf::Vector2i(m_widgetList.size(), m_widgetList[0].size());
	}

	const Widget* Layout::getWidget(const sf::Vector2i &pos) const
	{
		return getWidget(pos.x, pos.y);
	}

	const Widget* Layout::getWidget(unsigned int x, unsigned int y) const
	{
		sf::Vector2i widgetNullPos = hasBigWidget(sf::Vector2i(x, y));
		if(widgetNullPos == sf::Vector2i(-1, -1))
			return m_widgetList[x][y];
		else if(x < getSizeGrid().x && y < getSizeGrid().y)
			return m_widgetList[x][y];
		
		return NULL;
	}

	const sf::Vector2i& Layout::getVirtualDistance() const
	{
		return m_distance;
	}

	sf::Vector2i Layout::getRealDistance() const
	{
		return sf::Vector2i(m_distance.x * m_scale.x, m_distance.y * m_scale.y);
	}

	void Layout::resizeWidget(const sf::Vector2i& oldWindowSize, const sf::Vector2i& newWindowSize)
	{
		Widget::resizeWidget(oldWindowSize, newWindowSize);
		m_scale = sf::Vector2f(newWindowSize.x / oldWindowSize.x, newWindowSize.y/oldWindowSize.y);
	}

	sf::Vector2i Layout::hasBigWidget(const sf::Vector2i &pos) const
	{
		//See if there are a Widget in the case indicated with pos
		for(unsigned int i = 0; i < m_widgetList.size(); ++i)
		{
			for(unsigned int j = 0; j < m_widgetList[i].size(); ++j)
			{
				if(pos != sf::Vector2i(i, j))
				{
					sf::Vector2i sizeWidget = m_sizeWidget[i][j];
					if(i <= pos.x && j <= pos.y && sizeWidget.x >= pos.x && sizeWidget.y >= pos.y)
						return sf::Vector2i(i, j);
				}
			}
		}
		return sf::Vector2i(-1, -1);
	}

	int Layout::getNumberWidgetColumn(int pos) const
	{
		int nbColumn = 0;
		for(int j = 0; j < getSizeGrid().y; j++)
		{
			if(!(m_widgetList[pos][j]))
				nbColumn++;
		}

		return nbColumn;
	}

	const sf::Vector2i Layout::getPosWidget(const Widget& widget) const
	{
		for(unsigned int i = 0; i < getSizeGrid().x; ++i)
		{
			for(unsigned int j = 0; j < getSizeGrid().y; ++j)
			{
				if(m_widgetList[i][j] == &widget)
					return sf::Vector2i(i, j);
				else if(hasBigWidget(sf::Vector2i(i, j)) != sf::Vector2i(-1, -1))
					return hasBigWidget(sf::Vector2i(i, j));
			}
		}

		return sf::Vector2i(-1, -1);
	}
}
