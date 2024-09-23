#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <functional>
#include "InputManager.h"
#include "Button.h"

class GUIManager : public InputObserver
{
public:
	

	GUIManager(std::function<sf::RenderWindow&()> getWindowCB);

	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;

	void									InitButtons();
	void									AddButton(const sf::Vector2f& position);
	std::vector<std::unique_ptr<Button>>&	GetButtons();
	bool									GetButtonCondition() const;

	void									OnButtonUp();
	void									OnButtonDown();

private:
	bool									IsButtonDown;
	std::function<sf::RenderWindow&()>		mGetWindowCB;
	std::vector<std::unique_ptr<Button>>	mButtons;
};