#ifndef DEF_RENDER
#define DEF_RENDER

/*! \file Render.h
 *  \brief Basic virtual class for create Render's object. Window class and Frame class inherited of this class.
 *	\author Gaulois94
 *	\version 0.1
 *	\date 25 June 2012
 */

#include "Widget.h"
#include "Image.h"
#include "Slide.h"
#include "IRender.h"

namespace guiml
{
	/*! \class Render
	 *  \brief Basic virtual class for create Render's object. Window class and Frame class inherited of this class.
	 */
	class Render : public Widget, public IRender
	{
		public:
		#include "SurchargeMethode.h"

			/*! \brief The basic Render's constructor.
			 *	\param parent The object's parent.
			 *	\param rect Define the Render's position and size.
			 *	\param backgroundColor The color with which the Window is clean. At the default, the background color is Black.
			 *	\param backgroundImage If you want a background Image. At the default, the Window doesn't have a background image.
			 */
			Render(Updatable *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image());

			/*! \brief Set the background image.
			 *	\param backgroundImage The new background image.
			 */
			void setBackgroundImage(const Image &backgroundImage);

			/*! \brief Set the background color
			 *	\param backgroundColor The new background Color. 
			 */
			void setBackgroundColor(const sf::Color &backgroundColor);

			/*! \brief Set the title.
			 *	\param title The new title.
			 */
			virtual void setTitle(const std::string &title);

			/*! \brief Set the view. The class use this function for update his view (for example, if the user move the view with the moveView function, this function is call for update the view).
			 *	\param view The new view.
			 */
			virtual void setView(const sf::View &view);

			/*! \brief Move the view.
			 *	\param move The sf::Vector2f value for knowing that how many pixel the user want to move the view. 
			 */
			void moveView(const sf::Vector2f &move);

			/*! \brief Move the view.
			 *	\param x The value on "x" which the view is move.
			 *	\param y The value on "y" which the view is move.
			 */
			void moveView(float x, float y);
			
			/*! \brief Resize the Render's view.
			 *	\param resize The new view's size.
			 */
			void resizeView(const sf::Vector2f &resize);

			/*! \brief Resize the Render's view.
			 *	\param x The new view's size on "x".
			 *	\param y The new view's size on "y".
			 */
			void resizeView(float x, float y);

			/*! \brief Set Position of the Render's view.
			 *	\param position The new view's position.
			 */
			void setViewPosition(const sf::Vector2f &position);

			/*! \brief Set Position of the Render's view.
			 *	\param x The new view's position on "x".
			 *	\param y The new view's position on "y".
			 */
			void setViewPosition(float x, float y);
			
			void setViewSize(const sf::Vector2f &size);
			void setViewSize(float x, float y);

			/*! \brief Set the view's position and size.
			 *	\param rect The new position and size.
			 */
			void setViewport(const sf::FloatRect &rect);

			/*! \bief If you want to have the default view.
			 * 
			 */
			virtual void resetView() = 0;

			/*! \brief get the title.
			 */
			const std::string& getTitle() const;

			/*! \brief get the background image.
			 */
			const Image& getBackgroundImage() const;

			/*! \brief get the background color.
			 */
			const sf::Color& getBackgroundColor() const;

			/*! \brief get the view.
			 */
			virtual const sf::View& getView() const;

			/*! \brief get the view's rect.
			 */
			virtual sf::FloatRect getViewport() const;

			virtual sf::Vector2f getViewPosition() const;
			
			bool isInView(const sf::FloatRect &rect) const;
		protected:
			sf::View m_renderView; /*!< The Render view  */
			sf::FloatRect m_viewLimit; /*!< The limit of the view's position */
			sf::Color m_backgroundColor; /*!< The background color. */
			std::string m_renderTitle; /*!< The render's title. */
			Image m_backgroundImage; /*!< The background image.  */
			virtual void updateFocus();
	};
}

#endif
