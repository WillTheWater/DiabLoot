#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"
#include "GUIManager.h"

class RenderManager
{
public:
	RenderManager();

	sf::RenderWindow&							GetWindow();
	void										MainMenuRender();
	void										PlayRender();
	void										DrawButtons();

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	AssetManager								mAssetMgr;
	GUIManager									mGUIMgr;
	sf::RenderWindow							mGameWindow;
};