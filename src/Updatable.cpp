#include "Updatable.h"

bool guiml::Updatable::focusIsCheck = false;

namespace guiml
{

	Updatable::Updatable(Updatable *parent) : m_parent(NULL), m_changeWindow(false), m_event(NULL)
	{
		if(parent)
			parent->addChild(this);
	}

	Updatable::Updatable(const Updatable &copy) : m_parent(NULL), m_changeWindow(false), m_event(NULL)
	{}

	Updatable& Updatable::operator=(const Updatable &copy)
	{
		if(&copy != this)
		{
			m_parent = NULL;
			m_changeWindow = false;
		}
		return *this;
	}

	Updatable::~Updatable()
	{
		if(m_parent)
			m_parent->removeChild(this);

		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
		{
			if(*it)
				delete (*it);
			it = m_child.erase(it);
		}
	}

	void Updatable::updateFocus()
	{
		for(std::list<Updatable*>::reverse_iterator it = m_child.rbegin(); it != m_child.rend(); ++it)
		{
			if(Updatable::focusIsCheck == true)
			{
				focusIsCheck = false;
				return;
			}
			(*it)->updateFocus();
		}
	}

	void Updatable::update(IRender &render)
	{
		m_changeWindow = false;
		for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
			if(*it)
				(*it)->update(render);
	}

	void Updatable::addChild(Updatable *child, int pos)
	{
		if(child->m_parent != this)
			child->setParent(this, pos);

		if(child != NULL && !isChild(child))
		{
			if(pos < 0 || pos >= m_child.size())
				m_child.push_back(child);

			else
			{
				std::list<Updatable*>::iterator it = m_child.begin();
				for(unsigned int i = 0; i < pos; ++i)
					it++;
				m_child.insert(it, child);
			}
		}
	}

	void Updatable::setParent(Updatable *parent, int pos)
	{
		if(m_parent)
			m_parent->removeChild(this);
		
		EventManager* event = getEventManagerFromRootParent();
		m_parent = parent;	
		m_event = getEventManagerFromRootParent();
		
		if(event != m_event) //if the EventManager is not the same, then the Window's root parent is not the same. Then, we update the relative rect.
			m_changeWindow=true;

		if(parent)
			m_parent->addChild(this, pos);
	}

	bool Updatable::removeChild(Updatable *child)
	{
		if(child->getParent() == this)
			for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			{
				if(*it == child)
				{
					m_child.erase(it);
					child->m_parent = NULL;
					return true;
				}
			}
		return false;
	}

	bool Updatable::removeChild(unsigned int pos)
	{
		if(pos >= m_child.size())
			return false;

		std::list<Updatable*>::iterator it = m_child.begin();
		for(unsigned int i = 0; i != pos; i++)
			it++;

		(*it)->setParent(NULL);
		return true;
	}

	EventManager* Updatable::getEventManagerFromRootParent() const
	{
		if(m_parent == NULL)
			return NULL;
		return m_parent->getEventManagerFromRootParent();
	}

	bool Updatable::isChild(const Updatable *child)
	{
		bool isChild = false;

		for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			if((*it) == child)
			{
				isChild = true;
				break;
			}

		return isChild;
	}

	const Updatable* Updatable::getParent() const
	{
		return m_parent;
	}

	bool Updatable::hasChangeWindow() const
	{
		return m_changeWindow;
	}

	EventManager* Updatable::getEventManager()
	{
		return m_event;
	}

	sf::Vector2f Updatable::getRenderViewPosition() const
	{
		if(m_parent)
			return m_parent->getRenderViewPosition();
		else
			return sf::Vector2f(0, 0);
	}
}
