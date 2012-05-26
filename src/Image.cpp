#include "Image.h"

namespace guiml
{
	//-------------------------All constructor with various parameters--------------------------//
	Image::Image(Widget *parent, const std::string &path, const sf::IntRect &rect) : Widget(parent, rect)
	{
		try
		{
			if(!(m_texture.loadFromFile(path)))
				throw  std::runtime_error("FATAL ERROR : The path is invalid");
		}

		catch(const std::exception &error)
		{
			throw;
		}

		m_sprite.setTexture(m_texture);

		if (rect != sf::IntRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(sf::IntRect(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	}

	Image::Image(Widget *parent, const sf::Image &image, const sf::IntRect &rect) : Widget(parent, rect)
	{
		try
		{
			if(!(m_texture.loadFromImage(image)))
				throw std::string ("The image is invalid");
		}

		catch(const std::string &error)
		{
			std::cerr << error << std::endl;
		}

		m_sprite.setTexture(m_texture);
		if (rect != sf::IntRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(sf::IntRect(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	}

	Image::Image(Widget *parent, const sf::Texture &texture, const sf::IntRect &rect) : Widget(parent, rect), m_texture(texture)
	{
		m_sprite.setTexture(m_texture);
		if (rect != sf::IntRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(sf::IntRect(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	}

	Image::Image(Widget *parent, const sf::Sprite &sprite, const sf::IntRect &rect) : Widget(parent, rect)
	{
		setImage(sprite);
		if (rect != sf::IntRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(sf::IntRect(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	}

	Image::Image(Widget *parent) : Widget(parent)
	{}

	Image::Image() : Widget(NULL)
	{}

	Image::Image(const Image &copy) : Widget(copy), m_sprite(copy.m_sprite), m_texture(copy.m_texture)
	{}

	Image& Image::operator=(const Image &copy)
	{
		if(&copy != this)
		{
			Widget::operator=(copy);
			m_sprite = copy.m_sprite;
			m_texture = copy.m_texture;
		}

		return *this;
	}

	Image::~Image()
	{

	}
	//-----------------------------End of constructor------------------------------------------//

	void Image::update(std::list<sf::Drawable*> &drawable)
	{
		if(m_isDrawing)
			drawable.push_back(&m_sprite);
		Widget::update(drawable);
	}

	void Image::lighten(const sf::IntRect &rect)
	{
		if(m_virtualSize != sf::Vector2i(0, 0))
		{
			sf::IntRect rect2 = rect;
			sf::IntRect rect3 = getVirtualRect();
			if (rect == sf::IntRect(0, 0, 0, 0))
				rect2 = rect3;
			try
			{
				if(rect2.left + rect2.width > m_size.x || rect2.top + rect2.height > m_size.y)
					throw std::runtime_error("FATAL ERROR : The Plage color don't can be in the sprite");
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
				throw;
			}
		}
	}


	void Image::setPlageColor(const sf::IntRect &rect, const sf::Color &color)
	{
		try
		{
			if(rect.left + rect.width > m_virtualSize.x || rect.top + rect.height > m_virtualSize.y)
				throw std::runtime_error("FATAL ERROR : The Plage color don't can be in the sprite");
			else
				for(int i=0; i > rect.width; ++i)
					for(int j=0; j > rect.height; ++j)
						setColorPixel(rect.left + i, rect.top + j, color);
		}

		catch(const std::runtime_error &error)
		{
			throw;
		}
	}

	const sf::Sprite &Image::getSprite()
	{
		return m_sprite;
	}

	void Image::setPosition(int x, int y)
	{
		m_sprite.setPosition(x, y);
		Widget::setPosition(x, y);
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

	
	void Image::setColorPixel(float x, float y, const sf::Color &color)
	{
		sf::Image image = m_sprite.getTexture()->copyToImage();
		image.setPixel(x, y, color);
		m_texture.loadFromImage(image);
		m_sprite.setTexture(m_texture);
	}

	void Image::setRotation(float angle)
	{
		m_sprite.setRotation(angle);
		setRect(sf::IntRect(m_sprite.getGlobalBounds().left, m_sprite.getGlobalBounds().top, m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	}

	void Image::setTextureRect(const sf::IntRect &rect)
	{
		m_sprite.setTextureRect(rect);
	}

	void Image::setImage(const sf::Texture &texture)
	{
		m_texture = texture;
		m_sprite.setTexture(m_texture);
		setRect(getVirtualRect());
	}

	void Image::setImage(const sf::Sprite &sprite)
	{
		m_sprite = sprite;
		setRect(getVirtualRect());
	}

	void Image::setImage(const std::string &path)
	{
		try
		{
			if(!(m_texture.loadFromFile(path)))
				throw std::string ("The path is invalid");
		}

		catch(const std::string &error)
		{
			std::cerr << error << std::endl;
		}

		m_sprite.setTexture(m_texture);
		setRect(getVirtualRect());
	}

	void Image::setImage(const sf::Image &image)
	{
		try
		{
			if(!(m_texture.loadFromImage(image)))
				throw std::string ("The image is invalid");
		}

		catch(const std::string &error)
		{
			std::cerr << error << std::endl;
		}

		m_sprite.setTexture(m_texture);
		setRect(getVirtualRect());
	}
	
	void Image::setSize(int x, int y)
	{
		m_sprite.setScale(x/m_sprite.getLocalBounds().width, y/m_sprite.getLocalBounds().height);
		Widget::setSize(x, y);
	}

    Widget*	Image::copy() const
	{
		return new Image(*this);
	}
}
