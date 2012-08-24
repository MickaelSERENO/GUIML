#include "Image.h"

RessourcesManager<sf::Texture*> guiml::Image::Image::textures;

namespace guiml
{
	//-------------------------All constructor with various parameters--------------------------//
	Image::Image(Updatable *parent, const std::string &path, bool delTextureCreated, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0), m_delTextureCreated(delTextureCreated)
	{
		sf::Texture *texture;
		if(!Widget::fileLoading.existe(path))
		{
			texture = new sf::Texture();
			try
			{
				if(!(texture->loadFromFile(path)))
				{
					throw  std::runtime_error("FATAL ERROR");
				}
			}

			catch(const std::exception &error)
			{
				throw;
			}

			Widget::fileLoading.add(path, texture);
		}
		else
			texture = Widget::fileLoading.get(path);
		setImage(*(texture));

		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Updatable *parent, const sf::Image &image, bool delTextureCreated, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0), m_delTextureCreated(delTextureCreated)
	{
		sf::Texture *texture = new sf::Texture();
		try
		{
			if(!(texture->loadFromImage(image)))
				throw std::string ("The image is invalid");
		}

		catch(const std::string &error)
		{
			std::cerr << error << std::endl;
		}

		std::string name("texture");
		std::ostringstream number;
		number << Image::textures.getSize();
		name += number.str();
		Image::textures.add(name, texture);
		m_textureCreated.push_back(name);
		setImage(*texture);
		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Updatable *parent, const sf::Texture &texture, bool delTextureCreated, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0), m_delTextureCreated(delTextureCreated)
	{
		setImage(texture);
		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Updatable *parent, const sf::Sprite &sprite, bool delTextureCreated, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0), m_delTextureCreated(delTextureCreated)
	{
		setImage(sprite);
		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Updatable *parent) : Widget(parent), m_sizeRoundEdge(0), m_delTextureCreated(false)
	{}

	Image::Image(const Image &copy) : Widget(copy)
	{
		setImage(copy.m_sprite);
		m_sizeRoundEdge = copy.m_sizeRoundEdge;
		m_delTextureCreated = copy.m_delTextureCreated;
		m_textureCreated = copy.m_textureCreated;
	}

	Image& Image::operator=(const Image &copy)
	{
		if(&copy != this)
		{
			Widget::operator=(copy);
			m_sprite = copy.m_sprite;
			m_sizeRoundEdge = copy.m_sizeRoundEdge;
		m_delTextureCreated = copy.m_delTextureCreated;
		m_textureCreated = copy.m_textureCreated;
		}

		return *this;
	}

	Image::~Image()
	{
		if(m_delTextureCreated)
			for(unsigned int i=0; i < m_textureCreated.size(); ++i)
				Image::textures.remove(m_textureCreated[i]);
	}
	//-----------------------------End of constructor------------------------------------------//

	void Image::update(std::list<sf::Drawable*> &drawable)
	{
		if(m_isDrawing)
			drawable.push_back(&m_sprite);
		Updatable::update(drawable);
	}

	void Image::roundEdge(int size)
	{
		if(m_sprite.getTexture())
		{
			sf::Image image = m_sprite.getTexture()->copyToImage();
			for(int i = 0; i != size; i++)
			{
				sf::Vector2f topleft = circle(i, size, size, size);
				sf::Vector2f bottomleft = circle(i, size, m_sprite.getTexture()->getSize().y - size, size);

				sf::Vector2f topright = circle(i + m_sprite.getTexture()->getSize().x - size, m_sprite.getTexture()->getSize().x - size, size, size);
				sf::Vector2f bottomright = circle(i + m_sprite.getTexture()->getSize().x - size, m_sprite.getTexture()->getSize().x - size, m_sprite.getTexture()->getSize().y - size, size);

				for(int j = 0; j < topleft.y; j++)
				{
					sf::Color pixel = image.getPixel(i, j);
					pixel.a = 255 * (1.f - std::max(std::min((float((sqrt((float)((i-size)*(i-size) + (j-size)*(j-size)))-size+1)/2.f)), 1.f), 0.f));
					image.setPixel(i, j, pixel);
				}

				for(int j = m_sprite.getTexture()->getSize().y-1; j > bottomleft.x; j--)
				{
					sf::Color pixel = image.getPixel(i, j);
					pixel.a = 255 * (1.f - std::max(std::min((float((sqrt((float)((i-size)*(i-size) + (j-(m_sprite.getTexture()->getSize().y - size))*(j-(m_sprite.getTexture()->getSize().y - size))))-size+1)/2.f)), 1.f), 0.f));
					image.setPixel(i, j, pixel);
				}

				for(int j = 0; j < topright.y; j++)
				{
					sf::Color pixel = image.getPixel(i + m_sprite.getTexture()->getSize().x - size, j);
					pixel.a = 255 * (1.f - std::max(std::min((float((sqrt((float)((i-(m_sprite.getTexture()->getSize().x - size))*(i-(m_sprite.getTexture()->getSize().x - size)) + (j-size)*(j-size)))-size+1)/2.f)), 1.f), 0.f));
					image.setPixel(i + m_sprite.getTexture()->getSize().x - size, j, pixel);
				}

				for(int j = m_sprite.getTexture()->getSize().y -1; j > bottomright.x; j--)
				{
					sf::Color pixel = image.getPixel(i + m_sprite.getTexture()->getSize().x - size, j);
					pixel.a = 255 * (1.f - std::max(std::min((float((sqrt((float)((i-(m_sprite.getTexture()->getSize().x - size))*(i-(m_sprite.getTexture()->getSize().x - size)) + (j-(m_sprite.getTexture()->getSize().y - size))*(j-(m_sprite.getTexture()->getSize().y - size))))-size+1)/2.f)), 1.f), 0.f));
					image.setPixel(i + m_sprite.getTexture()->getSize().x - size, j, pixel);
				}
			}
			setImage(image);
			m_sizeRoundEdge = size;
		}

		else
		{
			sf::RenderTexture render;
			render.create(m_virtualSize.x, m_virtualSize.y);
			render.draw(m_sprite);
			render.display();
			sf::Texture *texture = new sf::Texture(render.getTexture());
			
			std::string name("texture");
			std::ostringstream number;
			number << Image::textures.getSize();
			name += number.str();
			Image::textures.add(name, texture);
			m_textureCreated.push_back(name);
			setImage(*texture);
			roundEdge(size);
		}
	}

	void Image::lighten(const sf::FloatRect &rect)
	{
		if(m_sprite.getTexture() && m_sprite.getTexture()->getSize() != sf::Vector2u(0, 0))
		{
			sf::FloatRect rect2;
			sf::FloatRect rect3 = m_sprite.getLocalBounds();
			if (rect == sf::FloatRect(0, 0, 0, 0))
				rect2 = rect3;
			else
			{
				rect2 = rect;
				rect2.width *= m_sprite.getLocalBounds().width / m_sprite.getGlobalBounds().width;
				rect2.height *= m_sprite.getLocalBounds().height / m_sprite.getGlobalBounds().height;
			}

			try
			{
				if(rect2.left + rect2.width > m_sprite.getLocalBounds().width || rect2.top + rect2.height > m_sprite.getLocalBounds().height)
					throw std::runtime_error("Error : The Plage color don't can be in the sprite");
				else
				{
					sf::Image image = m_sprite.getTexture()->copyToImage();
					for(float i=rect2.left; i < (rect2.left + rect2.width) ; i++)
						for(float j=rect2.top; j < (rect2.top + rect2.height); j++)
						{
							sf::Color pixel = image.getPixel(i, j);
							float c = float(pixel.r)/255;
							pixel.r = 255*(3*c*c-2*c*c*c);
							c = float(pixel.g)/255;
							pixel.g = 255*(3*c*c-2*c*c*c);
							c = float(pixel.b)/255;
							pixel.b = 255*(3*c*c-2*c*c*c);
		
							image.setPixel(i, j, pixel);
						}
					setImage(image);
				}
			}
			catch(const std::runtime_error &error)
			{
				std::cout << error.what() << std::endl;
			}
		}
	}

	const sf::Sprite &Image::getSprite() const
	{
		return m_sprite;
	}

	int Image::getSizeRoundEdge() const
	{
		return m_sizeRoundEdge;
	}

	bool Image::getDelTextureCreated() const
	{
		return m_delTextureCreated;
	}

	void Image::setOrigin(float x, float y)
	{
		m_sprite.setOrigin(x, y);
	}

	void Image::setOrigin(const sf::Vector2f &pos)
	{
		setOrigin(pos.x, pos.y);
	}

	void Image::setOriginMiddle()
	{
		setOrigin(m_virtualSize.x / 2, m_virtualSize.y / 2);
	}

	void Image::setColor(const sf::Color &color)
	{
		m_sprite.setColor(color);
	}

	void Image::setRotation(float angle)
	{
		m_sprite.setRotation(angle);
		setRect(m_sprite.getGlobalBounds());
	}

	void Image::setTextureRect(const sf::FloatRect &rect)
	{
		m_sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
	}

	void Image::setImage(const sf::Texture &texture)
	{
		m_sprite.setTexture(texture);
		setRect(getVirtualRect());
	}

	void Image::setImage(const sf::Sprite &sprite)
	{
		m_sprite = sprite;
		setRect(getVirtualRect());
	}

	void Image::setImage(const std::string &path)
	{
		sf::Texture *texture;
		if(!Widget::fileLoading.existe(path))
		{
			texture = new sf::Texture;
			try
			{
				if(!(texture->loadFromFile(path)))
					throw std::string ("The path is invalid");
			}

			catch(const std::string &error)
			{
				std::cerr << error << std::endl;
			}
			Widget::fileLoading.add(path, texture);
		}
		m_sprite.setTexture(*texture);
		setRect(getVirtualRect());
	}

	void Image::setImage(const sf::Image &image)
	{
		sf::Texture *texture = new sf::Texture;
		try
		{
			if(!(texture->loadFromImage(image)))
				throw std::string ("The image is invalid");
		}

		catch(const std::string &error)
		{
			std::cerr << error << std::endl;
		}

		std::string name("texture");
		std::ostringstream number;
		number << Image::textures.getSize();
		name += number.str();
		Image::textures.add(name, texture);
		m_textureCreated.push_back(name);
		m_sprite.setTexture(*texture);
		setRect(getVirtualRect());
	}
	
	void Image::setSize(float x, float y)
	{
		m_sprite.setScale(x/m_sprite.getLocalBounds().width, y/m_sprite.getLocalBounds().height);
		Widget::setSize(x, y);
	}

	void Image::setPosition(float x, float y)
	{
		m_sprite.setPosition(x, y);
		Widget::setPosition(x, y);
	}

	void Image::setDelTextureCreated(bool delTextureCreated)
	{
		m_delTextureCreated = delTextureCreated;
	}

    Widget*	Image::copy() const
	{
		return new Image(*this);
	}
}
