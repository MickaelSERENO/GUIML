#include "Image.h"

namespace guiml
{
	//-------------------------All constructor with various parameters--------------------------//
	Image::Image(Widget *parent, const std::string &path, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0)
	{
		try
		{
			if(!(m_texture.loadFromFile(path)))
			{
				throw  std::runtime_error("FATAL ERROR");
			}
		}

		catch(const std::exception &error)
		{
			throw;
		}

		m_sprite.setTexture(m_texture);

		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Widget *parent, const sf::Image &image, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0)
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
		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Widget *parent, const sf::Texture &texture, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0)
	{
		m_sprite.setTexture(m_texture);
		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Widget *parent, const sf::Sprite &sprite, const sf::FloatRect &rect) : Widget(parent, rect), m_sizeRoundEdge(0)
	{
		setImage(sprite);
		if (rect != sf::FloatRect(0, 0, 0, 0))
			setRect(rect);
		else
			setRect(m_sprite.getGlobalBounds());
	}

	Image::Image(Widget *parent) : Widget(parent), m_sizeRoundEdge(0)
	{}

	Image::Image(const Image &copy) : Widget(copy), m_sprite(copy.m_sprite)
	{
		if(copy.m_sprite.getTexture())
			setImage(copy.m_texture);
		else
			m_texture = sf::Texture();
		m_sizeRoundEdge = copy.m_sizeRoundEdge;
	}

	Image& Image::operator=(const Image &copy)
	{
		if(&copy != this)
		{
			Widget::operator=(copy);
			m_sprite = copy.m_sprite;
			if(copy.m_sprite.getTexture())
				setImage(copy.m_texture);
			else
				m_texture = sf::Texture();
			m_sizeRoundEdge = copy.m_sizeRoundEdge;
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
			sf::RenderTexture texture;
			texture.create(m_virtualSize.x, m_virtualSize.y);
			texture.draw(m_sprite);
			texture.display();
			m_texture = texture.getTexture();
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


	void Image::setPlageColor(const sf::FloatRect &rect, const sf::Color &color)
	{
		try
		{
			if(rect.left + rect.width > m_virtualSize.x || rect.top + rect.height > m_virtualSize.y)
				throw std::runtime_error("FATAL ERROR : The Plage color don't can be in the sprite");
			else
			{
				for(int i=0; i > rect.width*m_sprite.getLocalBounds().width/m_sprite.getGlobalBounds().height; ++i)
					for(int j=0; j > rect.height*m_sprite.getLocalBounds().width/m_sprite.getGlobalBounds().height; ++j)
						setColorPixel(rect.left + i, rect.top + j, color);
			}
		}
		catch(const std::runtime_error &error)
		{
			throw;
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
		setRect(m_sprite.getGlobalBounds());
	}

	void Image::setTextureRect(const sf::FloatRect &rect)
	{
		m_sprite.setTextureRect(sf::IntRect(rect.left, rect.top, rect.width, rect.height));
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
		if(sprite.getTexture())
			setImage(*(sprite.getTexture()));
		else
			m_texture = sf::Texture();
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

    Widget*	Image::copy() const
	{
		return new Image(*this);
	}
}
