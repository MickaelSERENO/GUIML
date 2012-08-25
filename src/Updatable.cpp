#include "Updatable.h"

namespace guiml
{

	Updatable::Updatable(Updatable *parent) : m_parent(NULL), m_changeWindow(false)
	{
		if(parent)
			parent->addChild(this);
	}

	Updatable::Updatable(const Updatable &copy) : m_parent(NULL), m_changeWindow(false)
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
			delete (*it);
			it = m_child.erase(it);
		}
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
		
		EventManager* event = getEventManager();
		m_parent = parent;	
		EventManager* newEvent = getEventManager();

		if(parent)
			m_parent->Updatable::addChild(this, pos);

		if(newEvent != NULL && event != newEvent) //if the EventManager is not the same, then the Window's root parent is not the same. Then, we update the relative rect.
			m_changeWindow=true;
	}

	bool Updatable::removeChild(Updatable *child)
	{
		if(child->getParent() == this)
		{
			child->setParent(NULL);
			return true;
		}

		else
		{
			for(std::list<Updatable*>::iterator it = m_child.begin(); it != m_child.end(); ++it)
			{
				if(*it == child)
				{
					m_child.erase(it);
					return true;
				}
			}
			return false;
		}
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

	EventManager* Updatable::getEventManager() const
	{
		if(m_parent == NULL)
			return NULL;
		return m_parent->getEventManager();
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

	void Updatable::update(std::list<sf::Drawable*> &drawables)
	{
		for(std::list<Updatable*>::iterator it = m_child.begin(); it!=m_child.end(); ++it)
			if(*it)
				(*it)->update(drawables);
	}

	const Updatable* Updatable::getParent() const
	{
		return m_parent;
	}
}
