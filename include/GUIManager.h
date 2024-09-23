#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "InputManager.h"
#include "Button.h"

class PlayState;
class GameState;

class GUIManager : public InputObserver
{
public:

	GUIManager();

	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;

	void									UpdateButtons();
	void									InitButtons(std::function<std::unique_ptr<PlayState>()> createPlayStateCB, std::function<void(std::unique_ptr<GameState>)> changeStateCB);
	void									SetWindowCB(std::function<sf::RenderWindow& ()> getWindowCB);
	Button*									AddButton(const sf::Vector2f& position, const std::string& buttonText);
	std::vector<std::unique_ptr<Button>>&	GetButtons();
	bool									GetButtonCondition() const;

	void									OnButtonUp();
	void									OnButtonDown();
	void									WasClicked(Button& button);


private:
	bool									IsButtonDown;
	std::function<sf::RenderWindow& ()>		mGetWindowCB;
	std::vector<std::unique_ptr<Button>>	mButtons;
};