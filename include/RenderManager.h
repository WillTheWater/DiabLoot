#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"
#include "Level.h"

class RenderManager
{
public:
	RenderManager();

	sf::RenderWindow&							GetWindow();
	AssetManager&								GetAssetManager();
	void										MainMenuRender();
	void										PlayRender();
	void										RenderLevel(Level& level);

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	AssetManager								mAssetMgr;
	sf::RenderWindow							mGameWindow;
	void										RenderParticles(std::vector<std::unique_ptr<Particle>>& particles);
	void										RenderChests(std::vector<std::unique_ptr<Chest>>& chests);
};