#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <functional>
#include "Assets.h"
#include "Button.h"

class PlayState;
class GameState;
class System;

class GUIManager
{
public:

	GUIManager(System& system);

	std::unique_ptr<Button>					MakeButton(const BUTTONS::BUTTON_TYPE& type, const BUTTONS::BUTTON_TEXT& text, const sf::Vector2f& position);
	std::unique_ptr<Button>					MakeInventoryButton(const BUTTONS::BUTTON_TYPE& type, const sf::Vector2f& position);
	void									UpdateButtons(sf::Vector2f mousePos, bool isClicked);
	std::vector<std::unique_ptr<Button>>&	GetButtons();
	void ButtonInit();
	Button& GetButton(BUTTONS::BUTTON_ID buttonID);
	void MainMenuUpdate(sf::Vector2f mousePos, bool isClicked);

private:
	sf::Vector2f							mWindowCenter;
	std::vector<std::unique_ptr<Button>>	mButtons;
	System& mSystem;
};