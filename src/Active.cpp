#include "Active.h"

namespace guiml
{
	Active::Active(bool select, bool active, bool alwaysUpdateSelection, bool alwaysUpdateActivation) : m_isSelect(select), m_isSelectCopy(select), m_isActive(active), m_isActiveCopy(active), m_alwaysUpdateSelection(alwaysUpdateSelection), m_alwaysUpdateActivation(alwaysUpdateActivation){}

	Active::Active(const Active &copy) : m_isSelect(copy.m_isSelect), m_isSelectCopy(copy.m_isSelectCopy), m_isActive(copy.m_isActive), m_isActiveCopy(copy.m_isActiveCopy), m_alwaysUpdateSelection(copy.m_alwaysUpdateSelection), m_alwaysUpdateActivation(copy.m_alwaysUpdateActivation){}

	Active& Active::operator=(const Active &copy)
	{
		if(this != &copy)
		{
			m_isSelect=copy.m_isSelect;
			m_isSelectCopy=copy.m_isSelectCopy;
			m_isActive=copy.m_isActive;
			m_isActiveCopy=copy.m_isActiveCopy;

			m_alwaysUpdateSelection=copy.m_alwaysUpdateSelection;
			m_alwaysUpdateActivation=copy.m_alwaysUpdateActivation;
		}

		return *this;
	}

	void Active::update()
	{
		if(!m_isSelectCopy || m_alwaysUpdateSelection)
			updateSelection();

		if(!m_isActiveCopy || m_alwaysUpdateActivation)
			updateActivation();
	}

	bool Active::updateSelection()
	{
		if(m_isSelect)
			selectIt();
		else
			deselectIt();

		return m_isSelect;
	}

	bool Active::updateActivation()
	{
		if(m_isActive)
			activeIt();
		else
			disactiveIt();

		return m_isActive;
	}

	void Active::selectIt()
	{
		m_isSelect = true;
	}

	void Active::deselectIt()
	{
		m_isSelect = false;
	}

	void Active::activeIt()
	{
		m_isActive = true;
	}

	void Active::disactiveIt()
	{
		m_isActive = false;
	}

	void Active::setPermanentSelection(bool permanentInSelection)
	{
		m_isSelectCopy = permanentInSelection;
		m_isSelect = permanentInSelection;
		updateSelection();
	}

	void Active::setPermanentActivation(bool permanentInActivation)
	{
		m_isActiveCopy = permanentInActivation;
		m_isActive = permanentInActivation;
		updateActivation();
	}

	void Active::setAlwaysUpdateSelection(bool alwaysUpdateSelection)
	{
		m_alwaysUpdateSelection = alwaysUpdateSelection;
	}

	void Active::setAlwaysUpdateActivation(bool alwaysUpdateActivation)
	{
		m_alwaysUpdateActivation = alwaysUpdateActivation;
	}

	bool Active::isPermanentSelect() const
	{
		return m_isSelectCopy;
	}

	bool Active::isPermanentActive() const
	{
		return m_isActiveCopy;
	}

	bool Active::isSelect() const
	{
		return m_isSelect;
	}

	bool Active::isActive() const
	{
		return m_isActive;
	}

	bool Active::isAlwaysUpdateSelection() const
	{
		return m_alwaysUpdateSelection;
	}

	bool Active::isAlwaysUpdateActivation() const
	{
		return m_alwaysUpdateActivation;
	}
}
