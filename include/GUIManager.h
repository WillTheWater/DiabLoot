#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "Button.h"

class PlayState;
class GameState;
class System;

class GUIManager
{
public:

	GUIManager(System& system);

	void									UpdateButtons();
	void									InitButtons(std::function<std::unique_ptr<PlayState>()> createPlayStateCB, std::function<void(std::unique_ptr<GameState>)> changeStateCB);
	void									SetWindowCB(std::function<sf::RenderWindow& ()> getWindowCB);
	Button* AddButton(const sf::Vector2f& position, const std::string& buttonText);
	std::vector<std::unique_ptr<Button>>& GetButtons();
	bool									GetButtonCondition() const;

	void									OnButtonUp();
	void									OnButtonDown();
	void									WasClicked(Button& button);

private:
	bool									IsButtonDown;
	std::function<sf::RenderWindow& ()>		mGetWindowCB;
	std::vector<std::unique_ptr<Button>>	mButtons;
	System& mSystem;
};