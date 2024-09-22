#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

class GUIManager
{
public:
	GUIManager();

	void									AddButton(const sf::Vector2f& position);
	void									UpdateButtons(const sf::Vector2f& mousePos, bool isClicked);
	std::vector<Button>&					GetButtons();

private:
	std::vector<Button>						mButtons;
};