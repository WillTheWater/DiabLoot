#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "AssetManager.h"
#include "Particle.h"
#include "Chest.h"

class RenderManager
{
public:
	RenderManager();

	sf::RenderWindow&							GetWindow();
	AssetManager&								GetAssetManager();
	void										MainMenuRender();
	void										PlayRender();
	void										RenderParticles(std::vector<std::unique_ptr<Particle>>& particles);
	void										RenderChests(std::vector<std::unique_ptr<Chest>>& chests);

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }

private:
	AssetManager								mAssetMgr;
	sf::RenderWindow							mGameWindow;
};