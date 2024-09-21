#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"

class RenderManager;

class GUIManager
{
public:
	GUIManager(RenderManager& renderMgr);

	void									AddButton(const sf::Vector2f& position);
	void									UpdateButtons(const sf::Vector2f& mousePos, bool isClicked);
	void									RenderButtons();

private:
	std::vector<Button>						mButtons;
	RenderManager&							mRenderMgr;
};