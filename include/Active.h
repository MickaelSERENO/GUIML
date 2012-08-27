#ifndef DEF_ACTIVE
#define DEF_ACTIVE

#include "Updatable.h"

namespace guiml
{
	class Active : public Updatable
	{
		public:
			Active(Updatable *parent, bool select = false, bool active = false, bool alwaysUpdateSelection = false, bool alwaysUpdateActivation = false);
			Active(const Active &copy);

			virtual void update(std::list<sf::Drawable*> drawable);

			virtual void updateSelection();
			virtual void updateActivation();

			virtual void selectIt();
			virtual void deselectIt();

			virtual void activeIt();
			virtual void disactiveIt();

			void setPermanentSelection(bool permamentInSelection);
			void setPermanentActivation(bool permamentInActivation);
			void setAlwaysUpdateSelection(bool alwaysUpdateSelection);
			void setAlwaysUpdateActivation(bool alwaysUpdateActivation);

			bool isSelect() const;
			bool isPermanentSelect() const;
			bool isAlwaysUpdateSelection() const;

			bool isActive() const;
			bool isPermanentActive() const;
			bool isAlwaysUpdateActivation() const;
		protected:
			bool m_isSelect;
			bool m_isSelectCopy;
			bool m_isActive;
			bool m_isActiveCopy;
			bool m_alwaysUpdateSelection;
			bool m_alwaysUpdateActivation;
	};
}
#endif
