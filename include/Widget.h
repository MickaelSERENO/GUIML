#ifndef DEF_WIDGET
#define DEF_WIDGET

/*! \file Widget.h
 * \brief Basic class for create Widgets.
 * \author Gaulois94
 * \version 0.1
 * \date 25 June 2012
 * */

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <stdexcept>
#include "EventManager.h"

/*! \namespace guiml
 *
 * Name's space who contain tool for create Widgets.
 */

namespace guiml
{
	/*!
	 * \class Widget
	 * \brief Root class for create Widgets.
	 */
	class Widget
	{
	public:
		/*! \brief Widget's Constructor
		 *
		 * \param parent The Widget parent who can update this object.
		 * \param rect Defined the Widget's position and size
		 * */
		Widget(Widget *parent, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));

		/*! \brief Widget's Copy Constructor.
		 * 
		 * \param copy The widget's copy
		 */
		Widget(const Widget &copy);

		/*! \brief Widget's virtual destructor. When the Widget is destroyed, all objects' child are destroyed this object will be delete in the parent's child's list.
		 * */
		virtual ~Widget();
	
		/*! \brief Add a child.
		 *
		 * \param child Widget who will be the child
		 * \param pos It indicated where the child will be place in the child's list (the order is important for the update's order). At the default, the child will be placed at the end of thechild's list.
		 * */
		virtual void addChild(Widget *child, int pos = -1);

		/*! \brief Set the Widget's parent.
		 *
		 *  \param parent The Widget who will be the parent.
		 *  \param pos The widget's position in the parent's child's list. At the default, the Widget will be placed at the end of the child's list.
		 * */
		void setParent(Widget *parent, int pos = -1);

		/*! \brief Remove the child of the Widget's child's list. It return true if the removing is correct, else it return false(maybe the parameter child is not a widget's child).
		 *
		 *  \param child The pointeur of the child who will be delete of the widget's child's list. 
		 */
		bool removeChild(Widget *child);

		/*! \brief Remove the child who is in the position indicate. It return true if the removing is correct, else it return false(maybe the position is wrong).
		 *
		 * \param pos The child's position in the Widget's child's list.
		 * */
		bool removeChild(unsigned int pos);

		/*! \brief Update the Widget or not.
		 * 
		 *	\param drawing Boolean for knowing if you want to update the widget or not.
		 */
		virtual void drawWidget(bool drawing);

		/*! \brief Update the Widget's children or not.
		 *  
		 *   \param drawing Boolean for knowing if you want to update the Widget's children or not.
		 */
		void drawAllChild(bool drawing);

		/*! \brief Update the Widget.
		 *
		 *	\param drawables List who will be complete by Widget's drawable. This function in this root class doesn't complete drawables (because he haven't) but it update all the Widget's child.
		 */
		virtual void update(std::list<sf::Drawable*> &drawables); //Update all Children of the Widget

		/*! \brief Set the absolute position (without Window's resize).
		 *
		 *	\param newPos The sf::Vector2f who contain the position on "x" and on "y"
		 * */
		virtual void setPosition(const sf::Vector2f &newPos);

		/*! \brief Set the absolute Widget's position (without Window's resize).
		 * 
		 *  \param x The position on "x"
		 *  \param y The position on "y" 
		 */
		virtual void setPosition(float x, float y);

		/*! \brief Set the absolute Widget's size (without Window's resize).
		 *
		 *  \param newSize The sf::Vector2f who contain the size on "x" and on "y"
		 * */
		virtual void setSize(const sf::Vector2f &newSize);

		/*! \brief Set the absolute Widget's size (without Window's resize).
		 *
		 *  \param x The Widget's size on "x"
		 *  \param y The Widget's size on "y"
		 */
		virtual void setSize(float x, float y);

		/*! \brief Move the Widget.
		 *
		 *  \param x The value on "x" of the Widget's moving.
		 *  \param y The value on "y" of the Widget's moving.
		 */
		void move(float x, float y);

		/*! \brief Move the Widget.
		 *
		 *  \param moving The sf::Vector2f who contain values on "x" and "y" of the Widget's moving. 
		 */
		void move(const sf::Vector2f &moving);

		/*! \brief Add values at the Widget's size.
		 *
		 *  \param addingSize The sf::Vector2f who contain values on "x" and "y", values who will be add at the Widget's size. 
		 */
		void addSize(const sf::Vector2f &addingSize);

		/*! \brief Add values at the Widget's size.
		 * 
		 *  \param x The value on "x" who will be add at the Widget's size (on "x").
		 *  \param y The value on "y" who will be add at the Widget's size (on "y").
		 */
		void addSize(float x, float y);

		/*! \brief Scale the Widget
		 * 
		 *  \param x The value on "x" of the Widget's scaling.
		 *  \param y The value on "y" of the Widget's scaling.
		 */
		virtual void scale(float x, float y);

		/*! \brief Scale the Widget
		 * 
		 *  \param scaling The sf::Vector2f who contain values for scalling the Widget.
		 */
		virtual void scale(const sf::Vector2f &scaling);

		/*! \brief Scale the Widget
		 * 
		 *  \param x This value represent the value on "x" and "y" for scalling the Widget.
		 */
		virtual void scale(float x);

		/*! \brief If you move the Widget, all child are also in moving.
		 *
		 * \param movingAllChild Boolean for knowing if you want moving all the Widget's child or not, if the Widget is in moving. 
		 */
		void moveAllChild(bool movingAllChild);

		/*! \brief Get m_movingAllChild's value. It say if all Widget's child can move or not, if the Widget is in moving.
		 */
		bool getMovingAllChild() const;

		/*! \brief Return m_isDrawing. It's a boolean for knowing if the Widget can be updated or not.
		 * */
		bool isDrawing() const;

		/*! \brief Return true if "child" is a Widget's child, els it return false.
		 *
		 *  \param child The Widget who can be a Widget's child.
		 * */
		bool isChild(const Widget *child);

		/*! \brief Return true if the Widget has a parent, else it return false.
		 */
		bool hasParent() const;

		/*! \brief If the root parent is a Window, this function return a pointeur about the Window's EventManager. Else, it return NULL.
		 */
		virtual EventManager* getEventManager() const; //get de EventManager who will be use for all of children.

		/*! \brief Return the relative Widget's position (with Window's resize).
		 */
		const sf::Vector2f& getPosition() const;

		/*! \brief Return the absolute Widget's position (without Window's resize).
		 */
		const sf::Vector2f& getVirtualPosition() const;

		/*! \brief Return the relative Widget's size (with Window's resize).
		 */
		const sf::Vector2f& getSize() const;

		/*! \brief Return the absolute Widget's size (without Window's resize).
		 */
		const sf::Vector2f& getVirtualSize() const; 


		/*! \brief Return the relative Widget's rect (with Window's resize).
		 */
		virtual sf::FloatRect getRect() const;

		/*! \brief Return the absolute Widget's rect (without Window's resize).
		 */
		virtual sf::FloatRect getVirtualRect() const;

		/*! \brief Set the relative Widget's rect (with Window's resize).
		 *
		 * \param rect The relative Widget's rect (with Window's resize).
		 */
		virtual void setRect(const sf::FloatRect &rect);

		/*! \brief Copy's Operator.
		 *
		 * \param copy The copy.
		 */
		virtual Widget& operator=(const Widget &copy);

		/*! \brief When the Window is resize, the virtualSize and virtualPos are set (for correspond with the screen. Indeed, the SFML resize also all of drawables who are displayed). You don't need to call this function.
		 *
		 * \param defaultWindow The Window's size without resize (with the mouse).
		 * \param newWindowSize The Window's size with resize (with the mouse).
		 */
		virtual void resizeWidget(const sf::Vector2f& defaultWindowSize, const sf::Vector2f& newWindowSize);

		/*! \brief It return a Widget's copy.
		 */
		virtual Widget* copy() const;
	protected:
		std::list <Widget*> m_child; /*!< Child's list. */
		Widget *m_parent; /*!< The Widget's parent. */
		bool m_isDrawing; /*!< Update the Widget or not ? */
		sf::Vector2f m_pos; /*!< The relative Widget's position (with Window's resize). */
		sf::Vector2f m_size; /*!< The relative Widget's size (with Window's resize). */
		sf::Vector2f m_virtualPos; /*!< The absolute Widget's position (without Window's resize). */
		sf::Vector2f m_virtualSize; /*!< The absolute Widget's size (without Window's resize). */
		bool m_movingAllChild; /*!< When the Widget's position is set, do we must moving the child ? */
	};
}

#endif
