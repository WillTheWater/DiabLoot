#include "InputManager.h"
#include "Core.h"

InputManager::InputManager()
{
	mObservers.reserve(100);
}

void InputManager::AddObserver(InputObserver* observer)
{
	if (std::find(mObservers.begin(), mObservers.end(), observer) != mObservers.end())
	{
		return;
	}

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
}

void InputManager::NotifyKeyPress(sf::Keyboard::Key key)
{
	for (auto observer : mObservers)
	{
		observer->OnKeyPress(key);
	}
}

void InputManager::NotifyKeyRelease(sf::Keyboard::Key key)
{
	for (auto observer : mObservers)
	{
		observer->OnKeyRelease(key);
	}
}

void InputManager::NotifyMouseClick(sf::Mouse::Button button)
{
	for (auto observer : mObservers)
	{
		observer->OnMouseClick(button);
	}
}

void InputManager::NotifyMouseRelease(sf::Mouse::Button button)
{
	for (auto observer : mObservers)
	{
		observer->OnMouseRelease(button);
	}
}