#include "EventManager.h"

EventManager::EventManager(sf::Window *win) : w(win), m_mousePos(0, 0), m_oldMousePos(0, 0), m_hasPressed(false), m_isResize(false), m_newSize(sf::Vector2i(w->getSize().x, w->getSize().y)), m_oldSize(sf::Vector2i(w->getSize())), m_defaultSize(w->getSize())
{
	for(unsigned int i = 0; i < NBR_KEYS; i++)
	{
		m_keys[i] = false; 
		m_isInputKey[i] = false;
	}

	for(unsigned int i = 0; i < NBR_CLICS; i++)
	{
		m_mouseClicked[i] = false;
	   	m_isInputMouse[i] = false;
	}

	m_elapsedTime = 0;
	m_enteredText = false;
}

EventManager::~EventManager()
{
	w = NULL;
}

void EventManager::update()
{
	m_elapsedTime = m_clock.getElapsedTime().asMilliseconds();
	m_clock.restart();
	m_oldMousePos = m_mousePos;

	if(m_hasPressed)
	{
		for(unsigned int i = 0; i < NBR_CLICS; i++)
			m_isInputMouse[i] = false;
		for(unsigned int i = 0; i < NBR_KEYS; i++)
			m_isInputKey[i] = false;
		m_hasPressed = false;
	}

	m_enteredText = false;
	m_isResize = false;

	while(w->pollEvent(m_event))
	{
		if(m_event.type == sf::Event::KeyReleased)
			if(m_event.key.code < static_cast<int>(NBR_KEYS))
			{
				m_keys[m_event.key.code] = false;
				m_isInputKey[m_event.key.code] = false;
			}

		if(m_event.type == sf::Event::KeyPressed)
			if(m_event.key.code < static_cast<int>(NBR_KEYS))
			{
				m_isInputKey[m_event.key.code] = true;
				m_keys[m_event.key.code] = true;
				m_hasPressed = true;
			}

		if(m_event.type == sf::Event::TextEntered)
			m_text = m_event.text.unicode, m_enteredText = true;

		if(m_event.type == sf::Event::MouseButtonReleased)
			if(m_event.mouseButton.button < static_cast<int>(NBR_CLICS))
			{
				m_mouseClicked[m_event.mouseButton.button] = m_isInputMouse[m_event.mouseButton.button] = false;
			}

		if(m_event.type == sf::Event::MouseButtonPressed)
			if(m_event.mouseButton.button < static_cast<int>(NBR_CLICS))
			{
				m_isInputMouse[m_event.mouseButton.button] = true;
				m_mouseClicked[m_event.mouseButton.button] = true;
				m_hasPressed = true;
			}

		if(m_event.type == sf::Event::MouseMoved)
		{
			m_oldMousePos = m_mousePos;
			m_mousePos = sf::Vector2i(m_event.mouseMove.x, m_event.mouseMove.y);
		}

		if(m_event.type == sf::Event::Closed)
			w->close();

		if(m_event.type == sf::Event::Resized)
		{
			if(m_newSize != sf::Vector2i(m_event.size.width, m_event.size.height))
			{
				m_isResize = true;
				m_oldSize = m_newSize;
				m_newSize = sf::Vector2i(m_event.size.width, m_event.size.height);
			}
		}
	}

	if(m_keys[sf::Keyboard::Back])
		m_enteredText = false;
}
	
void EventManager::setDefaultWindowSize(const sf::Vector2i& defaultWindowSize)
{
	m_defaultSize = defaultWindowSize;
}

bool EventManager::getPressedKey(unsigned int choice) const
{
	if(choice < NBR_KEYS)
		return m_keys[choice];
	return (false);
}

bool EventManager::getOnePressedKey(unsigned int choice) const
{
	if(choice < NBR_KEYS)
		return m_isInputKey[choice];
	return false;
}

bool EventManager::getOneMouseClicked(unsigned int choice) const
{
	if(choice < NBR_CLICS)
		return m_isInputMouse[choice];
	return false;
}

const sf::Uint32& EventManager::getText() const
{
	return m_text;
}

bool EventManager::isEnteredText() const
{
	return m_enteredText;
}

bool EventManager::getMouseClicked(unsigned int choice) const
{
	if(choice < NBR_KEYS)
		return m_mouseClicked[choice];
	return false;
}

const sf::Vector2i &EventManager::getMousePosition() const
{
	return m_mousePos;
}
 const sf::Vector2i &EventManager::getOldMousePosition() const
{
	return m_oldMousePos;
}

float EventManager::getElapsedTime() const
{
	return m_elapsedTime;
}

const sf::Event& EventManager::getEvent() const
{
	return m_event;
}

bool EventManager::hasPressed() const
{
	return m_hasPressed;
}

bool EventManager::windowIsResize() const
{
	return m_isResize;
}

const sf::Vector2i& EventManager::getNewWindowSize() const
{
	return m_newSize;
}

const sf::Vector2i& EventManager::getOldWindowSize() const
{
	return m_oldSize;
}

const sf::Vector2i& EventManager::getDefaultWindowSize() const
{
	return m_defaultSize;
}
