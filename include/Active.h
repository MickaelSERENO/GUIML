#ifndef DEF_ACTIVE
#define DEF_ACTIVE

namespace guiml
{
	class Active
	{
		public:
			Active(bool select = false, bool active = false, bool alwaysUpdateSelection = false, bool alwaysUpdateActivation = false);
			Active(const Active &copy);
			virtual Active& operator=(const Active &copy);

			virtual void update();

			virtual bool updateSelection();
			virtual bool updateActivation();

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
