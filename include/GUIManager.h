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

	void									MainMenuHUD();
	std::unique_ptr<Button>					MakeButton(const BUTTONS::BUTTON_TYPE& type, const BUTTONS::BUTTON_TEXT& text, const sf::Vector2f& position);
	std::unique_ptr<Button>					MakeInventoryButton(const BUTTONS::BUTTON_TYPE& type, const sf::Vector2f& position);
	void									UpdateButtons(const sf::Vector2f& mousePos, bool isClicked);
	std::vector<std::unique_ptr<Button>>&	GetButtons();

private:
	sf::Vector2f							mWindowCenter;
	std::vector<std::unique_ptr<Button>>	mButtons;
	System& mSystem;
};