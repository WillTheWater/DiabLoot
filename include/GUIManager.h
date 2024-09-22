#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "InputManager.h"
#include "Button.h"

class GUIManager : public InputObserver
{
public:
	GUIManager();

	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;

	void									AddButton(const sf::Vector2f& position);
	std::vector<std::unique_ptr<Button>>&	GetButtons();
	bool									GetButtonCondition() const;

	void									OnButtonUp();
	void									OnButtonDown();

private:
	bool									IsButtonDown;
	std::vector<std::unique_ptr<Button>>	mButtons;
};