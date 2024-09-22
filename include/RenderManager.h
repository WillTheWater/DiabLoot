#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"
#include "GUIManager.h"
#include "Level.h"

class RenderManager
{
public:
	RenderManager();

	sf::RenderWindow&							GetWindow();
	void									    MainMenuRender();
	void										DrawButtons();
	void										RenderLevel(Level& level);

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	AssetManager								mAssetMgr;
	GUIManager									mGUIMgr;
	sf::RenderWindow							mGameWindow;
	void										RenderParticles(std::vector<std::unique_ptr<Particle>>& particles);
	void										RenderChests(std::vector<std::unique_ptr<Chest>>& chests);
};