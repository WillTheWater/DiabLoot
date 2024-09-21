#pragma once
#include <vector>
#include <SFML/Window/Event.hpp>

class InputObserver
{
public:
	virtual void							OnMouseMove(int x, int y) = 0;
	virtual void							OnKeyPress(sf::Keyboard::Key key) = 0;
	virtual void							OnKeyRelease(sf::Keyboard::Key key) = 0;
	virtual void							OnMouseClick(sf::Mouse::Button button) = 0;
	virtual void							OnMouseRelease(sf::Mouse::Button button) = 0;
};

class InputManager
{
public:
	void									AddObserver(InputObserver* observer);
	void									RemoveObserver(InputObserver* observer);
	void									ProcessInput(sf::Event& event);

private:
	std::vector<InputObserver*>				mObservers;
	void									NotifyMouseMove(int x, int y);
	void									NotifyKeyPress(sf::Keyboard::Key key);
	void									NotifyKeyRelease(sf::Keyboard::Key key);
	void									NotifyMouseClick(sf::Mouse::Button button);
	void									NotifyMouseRelease(sf::Mouse::Button button);
};