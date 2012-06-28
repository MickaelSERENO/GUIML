#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
        sf::RenderWindow window(sf::VideoMode(800, 600, 32), std::string("teste"));
        sf::RenderTexture renderTexture;
        renderTexture.create(800, 600);
        sf::Image image;
        image.create(200, 85);
        sf::Texture texture;
        texture.loadFromImage(image);
        sf::Sprite sprite(texture);
        window.setFramerateLimit(60);   

        while(window.isOpen())
        {
                window.clear();
                renderTexture.clear(sf::Color::Blue);
                renderTexture.draw(sprite);
                renderTexture.display();
                sf::Sprite renderSprite(renderTexture.getTexture());
                window.draw(renderSprite);
                window.display();
        }
}
