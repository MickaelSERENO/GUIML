#ifndef DEF_IMAGE
#define DEF_IMAGE

#include "Widget.h"
#include <algorithm>
#include <sstream>

namespace guiml
{
	class Image : public Widget
	{
	public:
		#include "SurchargeMethode.h"
		//-------------one constructor for various parameters-------------//
		Image(Updatable *parent, const std::string &path, bool delTextureCreated = false, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Updatable *parent, const sf::Image &image, bool delTextureCreated = false, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Updatable *parent, const sf::Texture &texture, bool delTextureCreated  = false, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Updatable *parent, const sf::Sprite &sprite, bool delTextureCreated = false, const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		Image(Updatable *parent = NULL);
		Image(const Image &copy);
		Image& operator=(const Image &copy);

		virtual ~Image();
		//-----------------------and of constructor----------------------//

		virtual void draw(IRender &render); //methode Show version guiml::Image
		void lighten(const sf::FloatRect &rect = sf::FloatRect(0, 0, 0, 0));
		void roundEdge(int size);
		const sf::Sprite &getSprite() const; //return the sprite
		int getSizeRoundEdge() const;
		bool getDelTextureCreated() const;	
		sf::FloatRect getRect() const;

		void setColor(const sf::Color &color);

		void setTextureRect(const sf::FloatRect &rect);
		void setRotation(float angle);

		void setImage(const sf::Texture &texture, bool resetRect = false);
		void setImage(const sf::Sprite &sprite);
		void setImage(const std::string &path);
		void setImage(const sf::Image &image);
		void setSize(float x, float y);
		void setPosition(float x, float y, bool withOrigin=true);
		void setDelTextureCreated(bool delTextureCreated);

		Widget* copy() const;
	protected:
		sf::Sprite m_sprite; //the sprite of the image
		static RessourcesManager<sf::Texture*> textures;
		sf::Texture *spriteTexture;
		int m_sizeRoundEdge;
		bool m_delTextureCreated;
		std::vector<std::string> m_textureCreated;
	};
}

#endif
