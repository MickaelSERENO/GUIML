#ifndef DEF_WINDOW
#define DEF_WINDOW

/*! \file Window.h
 *  \brief Create and manage a Window. Generally, this object is a root object parent.
 *  \author Gaulois94
 *  \version 0.1
 *  \date 25 June 2012
 */

#include "EventManager.h"
#include "Image.h"
#include "Render.h"

namespace guiml
{
	/*! \class Window
	 * \brief Create and manage a Window.
	 */
	class Window : public Render, public sf::RenderWindow
	{
	public:
		/*! \brief Window's Constructor
		 *	\param mode A sf::VideoMode. It contain the size and de bit pixel.
		 *	\param title The Window's title.
		 *	\param parent The Window parent. Generally, parent = NULL because a Window is a root object parent of everything.
		 *	\param framerateLimit The Window's framerate limit. At the default, the framerate Limit is 60.
		 *	\param backgroundColor The color with which the Window is clean. At the default, the background color is Black.
		 *	\param backgroundImage If you want a background Image. At the default, the Window doesn't have a background image.
		 */
		Window(const sf::VideoMode &mode, const std::string &title, Updatable *parent = NULL, unsigned int framerateLimit = 60, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image());

		/*! \brief The virtual Window destructor. It delete m_event.
		 */
		virtual ~Window();

		/*! \brief Update the Window : get all Widget's child drawables. It update the EventManager too. After, it call the show method.
		 */
		void update();

		/*! \brief Update the Window : get all Widget's child drawables. It update the EventManager too. After, it call the show method.
		 * \param drawable You can, if you want, give a drawables's list. The Window, in the order, go to draw all drawable who contain "drawable".
		 */
		void update(std::list<sf::Drawable*> &drawable); 

		/*! \brief Draw and display all sf::Drawable that contain drawable.
		 * \param drawable All sf::Drawable that Window will draw and display. It draw drawable in the order of the list.
		 */
		void show(std::list<sf::Drawable*> &drawable); 

		void setPosition(float x, float y);
		void setSize(float x, float y);
		virtual void setTitle(const std::string &title);
		void setView(const sf::View &view);
		virtual void setParent(Updatable* parent, int pos = -1);
		void resetView();

		unsigned int getFramerate();
		virtual void resizeWidget(const sf::Vector2f& defaultWindowSize, const sf::Vector2f& newWindowSize);
	protected:
		float m_framerate;
	};
}

#endif
