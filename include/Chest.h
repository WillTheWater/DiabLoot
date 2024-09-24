#pragma once
#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include "Vec2.h"
#include "functional"

class Chest : public InputObserver
{
public:
	Chest(sf::Vector2f position, bool mirrored, std::function<void(Chest&)> callback);

	// Observer overrides
	void								OnMouseMove(int x, int y) override;
	void								OnKeyPress(sf::Keyboard::Key key) override;
	void								OnKeyRelease(sf::Keyboard::Key key) override;
	void								OnMouseClick(sf::Mouse::Button button) override;
	void								OnMouseRelease(sf::Mouse::Button button) override;
	// Functions
	void								OpenChest();
	sf::Vector2f						GetPosition() const;
	bool								IsOpened() const;
	bool								IsMirrored() const;

private:
	bool								mMirrored;
	bool								mOpened;
	sf::Vector2f						mPos;
	sf::RectangleShape					mRect;
	bool								mMouseOver;
	std::function<void(Chest&)>			mCallback;
};