#ifndef DEF_RENDER
#define DEF_RENDER

#include "Widget.h"
#include "Image.h"

namespace guiml
{
	class Render : public Widget
	{
		public:
			Render(Widget *parent, const sf::IntRect &rect, const sf::Color &backgroundColor = sf::Color::Black, const Image &backgroundImage = Image());
			virtual void show(std::list<sf::Drawable*> &drawable) = 0;

			void setBackgroundImage(const Image &backgroundImage);
			void setBackgroundColor(const sf::Color &backgroundColor);
			virtual void setTitle(const std::string &title);
			virtual void setView(const sf::View &view);
			void moveView(const sf::Vector2i &move);
			void moveView(int x, int y);
			virtual void resetView() = 0;

			const std::string& getTitle() const;
			const Image& getBackgroundImage() const;
			const sf::Color& getBackgroundColor() const;
			virtual const sf::View& getView() const;
			virtual sf::FloatRect getViewport() const;
		protected:
			sf::View m_renderView;
			sf::IntRect m_viewLimit;
			sf::Color m_backgroundColor;
			std::string m_windowTitle;
			Image m_backgroundImage;
	};
}

#endif
