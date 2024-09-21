#include "InputManager.h"
#include "Core.h"

void InputManager::AddObserver(InputObserver* observer)
{
	mObservers.push_back(observer);
}

void InputManager::RemoveObserver(InputObserver* observer)
{
	mObservers.erase(std::remove(mObservers.begin(), mObservers.end(), observer), mObservers.end());
}

void InputManager::ProcessInput(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
		NotifyMouseMove(event.mouseMove.x, event.mouseMove.y);
			break;
	case sf::Event::KeyPressed:
		NotifyKeyPress(event.key.code);
		break;
	case sf::Event::KeyReleased:
		NotifyKeyRelease(event.key.code);
		break;
	case sf::Event::MouseButtonPressed:
		NotifyMouseClick(event.mouseButton.button);
		break;
	case sf::Event::MouseButtonReleased:
		NotifyMouseRelease(event.mouseButton.button);
		break;
	default:
		break;
	}
}

void InputManager::NotifyMouseMove(int x, int y)
{
	for (auto observer : mObservers)
	{
		observer->OnMouseMove(x, y);
	}
	LOG("Mouse moved")
}

void InputManager::NotifyKeyPress(sf::Keyboard::Key key)
{
	for (auto observer : mObservers)
	{
		observer->OnKeyPress(key);
	}
	LOG("Key pressed")
}

void InputManager::NotifyKeyRelease(sf::Keyboard::Key key)
{
	for (auto observer : mObservers)
	{
		observer->OnKeyRelease(key);
	}
	LOG("Key released")
}

void InputManager::NotifyMouseClick(sf::Mouse::Button button)
{
	for (auto observer : mObservers)
	{
		observer->OnMouseClick(button);
	}
	LOG("Mouse clicked")
}

void InputManager::NotifyMouseRelease(sf::Mouse::Button button)
{
	for (auto observer : mObservers)
	{
		observer->OnMouseRelease(button);
	}
	LOG("Mouse released")
}