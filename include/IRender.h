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
	};
}

#endif
