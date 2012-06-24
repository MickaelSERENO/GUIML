#ifndef DEF_RENDER
#define DEF_RENDER

#include "Widget.h"
#include "Image.h"
#include "Slide.h"

namespace guiml
{
	class Render : public Widget
	{
		public:
		#include "SurchargeMethode.h"
			Render(Widget *parent, const sf::FloatRect &rect, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image(), int maxValueVerticalSlide=0, int maxValueHorizontalSlide=0);
			virtual void show(std::list<sf::Drawable*> &drawable) = 0;

			void setBackgroundImage(const Image &backgroundImage);
			void setBackgroundColor(const sf::Color &backgroundColor);
			virtual void setTitle(const std::string &title);
			virtual void setView(const sf::View &view);
			void moveView(const sf::Vector2f &move);
			void moveView(int x, int y);
			
			void resizeView(const sf::Vector2f &resize);
			void resizeView(int x, int y);

			void setViewPosition(const sf::Vector2f &position);
			void setViewPosition(int x, int y);
			
			void setRectView(const sf::FloatRect &rect);

			virtual void resetView() = 0;

			const std::string& getTitle() const;
			const Image& getBackgroundImage() const;
			const sf::Color& getBackgroundColor() const;
			virtual const sf::View& getView() const;
			virtual sf::FloatRect getViewport() const;
		protected:
			sf::View m_renderView;
			sf::FloatRect m_viewLimit;
			sf::Color m_backgroundColor;
			std::string m_windowTitle;
			Image m_backgroundImage;
			Slide m_verticalSlide;
			Slide m_horizontalSlide;
			
			int m_maxValueVerticalSlide;
			int m_maxValueHorisontalSlide;
	};
}

#endif
