#ifndef DEF_WIDGET
#define DEF_WIDGET

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <stdexcept>
#include "EventManager.h"

namespace guiml
{
	class Widget
	{
	public:
		Widget(Widget *parent, const sf::IntRect &rect = sf::IntRect(0, 0, 0, 0));
		Widget(const Widget &copy);

		virtual ~Widget();
	
		virtual void addChild(Widget *child, int pos = -1); //add a child of the widget
		void setParent(Widget *parent, int pos = -1); //set parent of the widget
		void removeChild(Widget *child); //remove one child of the widget
		virtual void drawWidget(bool drawing); //You can, if you want, draw or don't draw the widget
		void drawAllChild(bool drawing); //it simular that DrawWidget but is for all Children.

		virtual void update(std::list<sf::Drawable*> &drawables); //Update all Children of the Widget

		virtual void setPosition(const sf::Vector2i &newPos);
		virtual void setPosition(int x, int y);
		virtual void setSize(const sf::Vector2i &newSize);
		virtual void setSize(int x, int y);
		void move(int x, int y);
		void move(const sf::Vector2i &moving);
		void addSize(const sf::Vector2i &addingSize);
		void addSize(int x, int y);
		virtual void scale(float x, float y);
		virtual void scale(const sf::Vector2f &scaling);
		virtual void scale(float x);
		void moveAllChild(bool movingAllChild);

		bool getMovingAllChild() const;

		bool isDrawing() const; //boolean for know if this Widgets drawing or no.
		bool isChild(const Widget *child);
		bool hasParent() const;
		virtual EventManager* getEventManager() const; //get de EventManager who will be use for all of children.

		const sf::Vector2i& getPosition() const;
		const sf::Vector2i& getVirtualPosition() const;
		const sf::Vector2i& getSize() const;
		const sf::Vector2i& getVirtualSize() const; 

		virtual sf::IntRect getRect() const;
		virtual sf::IntRect getVirtualRect() const;

		virtual void setRect(const sf::IntRect &rect);
		virtual Widget& operator=(const Widget &copy);
		virtual void resizeWidget(const sf::Vector2i& defaultWindowSize, const sf::Vector2i& newWindowSize);
		virtual Widget* copy() const;
	protected:
		std::list <Widget*> m_child;
		Widget *m_parent;
		bool m_isDrawing;
		sf::Vector2i m_pos;
		sf::Vector2i m_size;
		sf::Vector2i m_virtualPos;
		sf::Vector2i m_virtualSize;
		bool m_movingAllChild;
	};
}

#endif
