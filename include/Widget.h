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
#include "RessourcesManager.h"
#include "Updatable.h"

/*! \namespace guiml
 *
 * Name's space who contain tool for create Widgets.
 */

namespace guiml
{
	enum Position
	{
		TopRight,
		TopLeft,
		Center,
		BottomRight,
		BottomLeft,
		Other
	};

	/*!
	 * \class Widget
	 * \brief Root class for create Widgets.
	 */
	class Widget : public Updatable
	{
	public:
		/*! \brief Widget's Constructor
		 *
		 * \param parent The Widget parent who can update this object.
		 * \param rect Defined the Widget's position and size
		 * */
		Widget(Updatable *parent, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));

		/*! \brief Widget's Copy Constructor.
		 * 
		 * \param copy The widget's copy
		 */
		Widget(const Widget &copy);


		/*! \brief Update the Widget.
		 *
		 *	\param drawables List who will be complete by Widget's drawable. This function in this root class doesn't complete drawables (because he haven't) but it update all the Widget's child.
		 */
		virtual void update(IRender &render);

		virtual void draw(IRender &render);

		/*! \brief Update the Widget or not.
		 * 
		 *	\param drawing Boolean for knowing if you want to update the widget or not.
	 */
		virtual void drawWidget(bool drawing);

		void setUpdateFocus(bool focus);
		void setStaticToView(bool dontMove, bool changePosition = false);
		/*! \brief Update the Widget's children or not.
		 *  
		 *   \param drawing Boolean for knowing if you want to update the Widget's children or not.
		 */
		void drawAllChild(bool drawing);

		void setOrigin(float x, float y);
		void setOrigin(const sf::Vector2f &origin);
		void setPosOrigin(const Position& position);

		/*! \brief Set the absolute position (without Window's resize).
		 *
		 *	\param newPos The sf::Vector2f who contain the position on "x" and on "y"
		 * */
		virtual void setPosition(const sf::Vector2f &newPos, bool withOrigin=true);

		/*! \brief Set the absolute Widget's position (without Window's resize).
		 * 
		 *  \param x The position on "x"
		 *  \param y The position on "y" 
		 */
		virtual void setPosition(float x, float y, bool withOrigin=true);

		void setPositionOnScreen(float x, float y, bool withOrigin=true);

		void setPositionOnScreen(const sf::Vector2f &pos, bool withOrigin=true);

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

		virtual void setScale(float x, float y);
		virtual void setScale(const sf::Vector2f &scaling);
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

		bool isStaticToView() const;

		/*! \brief Return the relative Widget's position (with Window's resize).
		 */

		bool getUpdateFocus() const;
		const sf::Vector2f& getOrigin() const;
		Position getPosOrigin() const;

		/*! \brief Return the absolute Widget's position (without Window's resize).
		 */
		sf::Vector2f getPosition(bool withOrigin=true) const;
		sf::Vector2f getVirtualPosition(bool withOrigin=true) const;

		sf::Vector2f getPosOnScreen(bool withOrigin=true);

		sf::Vector2f getVirtualPosOnScreen(bool withOrigin = true);

		/*! \brief Return the relative Widget's size (with Window's resize).
		 */
		const sf::Vector2f& getSize() const;

		/*! \brief Return the absolute Widget's size (without Window's resize).
		 */
		const sf::Vector2f& getVirtualSize() const; 
		const sf::Vector2f& getScale() const;

		/*! \brief Return the relative Widget's rect (with Window's resize).
		 */
		virtual sf::FloatRect getRect() const;

		/*! \brief Return the absolute Widget's rect (without Window's resize).
		 */
		virtual sf::FloatRect getVirtualRect() const;

		sf::FloatRect getRectOnScreen();

		sf::FloatRect getVirtualRectOnScreen();

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
		virtual Widget* copy() const;
		static const Widget* getFocus();
	protected:
		bool m_isDrawing; /*!< Update the Widget or not ? */
		bool m_isStaticToView;
		sf::Vector2f m_origin;
		sf::Vector2f m_pos; /*!< The relative Widget's position (with Window's resize). */
		sf::Vector2f m_size; /*!< The relative Widget's size (with Window's resize). */
		sf::Vector2f m_virtualPos; /*!< The absolute Widget's position (without Window's resize). */
		sf::Vector2f m_virtualSize; /*!< The absolute Widget's size (without Window's resize). */
		sf::Vector2f m_scale;
		bool m_movingAllChild; /*!< When the Widget's position is set, do we must moving the child ? */
		std::list<Widget*> m_widgetChild;
		bool m_focus;
		Position m_posOrigin;

		static RessourcesManager<sf::Texture*> fileLoading;
		static Widget* widgetMouseSelect;
		virtual void updateFocus();
	};
}

#endif
