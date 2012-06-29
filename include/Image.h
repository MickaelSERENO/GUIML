#ifndef DEF_IMAGE
#define DEF_IMAGE

#include "Widget.h"
#include "equation.h"
#include <algorithm>

namespace guiml
{
	class Image : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		//-------------one constructor for various parameters-------------//
		Image(Widget *parent, const std::string &path, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Widget *parent, const sf::Image &image, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Widget *parent, const sf::Texture &texture, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Widget *parent, const sf::Sprite &sprite, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Widget *parent);
		Image();
		Image(const Image &copy);
		Image& operator=(const Image &copy);

		virtual ~Image();
		//-----------------------and of constructor----------------------//

		virtual void update(std::list<sf::Drawable*> &drawable); //methode Show version guiml::Image
		void lighten(const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		void roundEdge(int size);
		const sf::Sprite &getSprite(); //return the sprite
			
		void setOrigin(float x, float y);
		void setOrigin(const sf::Vector2f &pos);
		void setOriginMiddle();
		void setColor(const sf::Color &color);
		void setColorPixel(float x, float y, const sf::Color &color);
		void setPlageColor(const sf::FloatRect &rect, const sf::Color &color);

		void setTextureRect(const sf::FloatRect &rect);
		void setRotation(float angle);

		void setImage(const sf::Texture &texture);
		void setImage(const sf::Sprite &sprite);
		void setImage(const std::string &path);
		void setImage(const sf::Image &image);
		void setSize(float x, float y);
		void setPosition(float x, float y);

		Widget* copy() const;
	protected:
		sf::Sprite m_sprite; //the sprite of the image
		sf::Texture m_texture;
	};
}

#endif
