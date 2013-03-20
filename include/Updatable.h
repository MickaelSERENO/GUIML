#ifndef DEF_UPDATABLE
#define DEF_UPDATABLE

#include <list>
#include <iostream>
#include <stdexcept>
#include "equation.h"
#include "EventManager.h"
#include "IRender.h"

namespace guiml
{
	class Updatable
	{
		public:
			Updatable(Updatable *parent);
			Updatable(const Updatable &copy);
			Updatable& operator=(const Updatable &copy);

			virtual ~Updatable();

			/*! \brief Update the Updatable.
			 *
			 *	\param drawables List who will be complete by Updatable's drawable. This function in this root class doesn't complete drawables (because he haven't) but it update all the Updatable's child.
			 */
			virtual void update(IRender &render);

			/*! \brief Add a child.
			 *
			 * \param child Updatable who will be the child
			 * \param pos It indicated where the child will be place in the child's list (the order is important for the update's order). At the default, the child will be placed at the end of thechild's list.
			 * */
			virtual void addChild(Updatable *child, int pos = -1);

			/*! \brief Set the Updatable's parent.
			 *
			 *  \param parent The Updatable who will be the parent.
			 *  \param pos The widget's position in the parent's child's list. At the default, the Updatable will be placed at the end of the child's list.
			 * */
			virtual void setParent(Updatable *parent, int pos = -1);

			/*! \brief Remove the child of the Updatable's child's list. It return true if the removing is correct, else it return false(maybe the parameter child is not a widget's child).
			 *
			 *  \param child The pointeur of the child who will be delete of the widget's child's list. 
			 */
			virtual bool removeChild(Updatable *child);

			/*! \brief Remove the child who is in the position indicate. It return true if the removing is correct, else it return false(maybe the position is wrong).
			 *
			 * \param pos The child's position in the Updatable's child's list.
			 * */
			bool removeChild(unsigned int pos);

			/*! \brief Return true if "child" is a Updatable's child, els it return false.
			 *
			 *  \param child The Updatable who can be a Updatable's child.
			 * */
			bool isChild(const Updatable *child);

			/*! \brief Return Updatable's parent.
			*/
			const Updatable* getParent() const;

			/*! \brief If the root parent is a Window, this function return a pointeur about the Window's EventManager. Else, it return NULL.
			*/

			bool hasChangeWindow() const;
			EventManager* getEventManager();
			virtual sf::Vector2f getRenderViewPosition() const;

		protected:
			std::list <Updatable*> m_child; /*!< Child's list. */
			Updatable *m_parent; /*!< The Updatable's parent. */
			EventManager *m_event;
			bool m_changeWindow; /*!< If Window is change in the setParent's function */
			static bool focusIsCheck;

			template <typename T>
			std::list<T*> extractFromUpdatableChild() const
			{
				return extractFromUpdatableList<T>(m_child);
			}

			template <typename T>
			std::list<T*> extractFromUpdatableList(std::list<Updatable*> fromExtract) const
			{
				std::list<T*> list;
				for(std::list<Updatable*>::const_iterator it = fromExtract.begin(); it != fromExtract.end(); ++it)
					if(T* extracted = dynamic_cast<T*>(*it))
						list.push_back(extracted);

				return list;
			}

			virtual EventManager* getEventManagerFromRootParent() const;
			virtual void updateFocus();
	};
}

#endif
