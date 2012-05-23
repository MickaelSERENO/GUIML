#ifndef DEF_EVENTMANAGER
#define DEF_EVENTMANAGER

#include <SFML/Graphics.hpp>
#include <iostream>

const unsigned int NBR_KEYS = 321;
const unsigned int NBR_CLICS = 3;

class EventManager
{
public:
	EventManager(sf::Window *win);
	~EventManager();
	void update(); //Update events
	void setDefaultWindowSize(const sf::Vector2i& defaultWindowSize);

	bool getPressedKey(unsigned int choice) const; //get the key who corresponds of the choice
	bool getOnePressedKey(unsigned int choice) const;
	const sf::Uint32& getText() const;
	bool isEnteredText() const;
	bool getMouseClicked(unsigned int choice) const; //get the key of the mouse who corresponds of the choice
	bool getOneMouseClicked(unsigned int choice) const;
	const sf::Vector2i &getMousePosition() const; //get the position of the mouse
	const sf::Vector2i &getOldMousePosition() const;
	template <typename T>
	bool isMouseInRect(const sf::Rect<T> &rect) const //See if the mouse is in the area of rect.
	{
		if(m_mousePos.x > rect.left
		&& m_mousePos.x < rect.left + rect.width
		&& m_mousePos.y > rect.top
		&& m_mousePos.y < rect.top + rect.height)
			return true;
		return false;
	}

	float getElapsedTime() const; //Return the time sell between two frames in microSeconds
	const sf::Event& getEvent() const;
	bool hasPressedKeyMouse() const;
	bool hasPressedKeyKey() const;
	bool windowIsResize() const;
	const sf::Vector2i& getNewWindowSize() const;
	const sf::Vector2i& getOldWindowSize() const;
	const sf::Vector2i& getDefaultWindowSize() const;
private:
	sf::Window *w;
	sf::Event m_event;
	bool m_keys[NBR_KEYS];
	sf::Uint32 m_text;
	bool m_enteredText;
	bool m_mouseClicked[NBR_CLICS];
	sf::Vector2i m_mousePos;
	sf::Vector2i m_oldMousePos;
	float m_elapsedTime;
	sf::Clock m_clock;
	bool m_isInputKey[NBR_KEYS];
	bool m_isInputMouse[NBR_CLICS];
	bool m_hasPressedKeyMouse;
	bool m_hasPressedKeyKey;
	bool m_isResize;
	sf::Vector2i m_newSize;
	sf::Vector2i m_oldSize;
	sf::Vector2i m_defaultSize;
};

#endif
