#ifndef DEF_IRENDER
#define DEF_IRENDER

#include <SFML/Graphics.hpp>

namespace guiml
{
	class IRender
	{
		public:
			IRender();
			virtual void draw(const sf::Drawable &drawable, const sf::RenderStates &states=sf::RenderStates::Default)=0;
			virtual bool isInView(const sf::FloatRect &rect) const=0;
			virtual sf::Vector2f getViewPosition() const=0;
			virtual sf::FloatRect getViewport() const=0;
			virtual const sf::View& getView() const=0;
	};
}

#endif
