#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"

class RenderManager
{
public:
	RenderManager();

	sf::RenderWindow&							GetWindow();
	AssetManager&								GetAssetManager();
	void										MainMenuRender();
	void										PlayRender();

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	AssetManager								mAssetMgr;
	sf::RenderWindow							mGameWindow;
};