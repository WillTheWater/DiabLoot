#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include "Inventory.h"

class System;

class RenderManager
{
public:
	RenderManager(System& system);

	sf::RenderWindow& GetWindow();

	void										MainMenuRender();

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }
	void										RenderLevel(Level& level);
	void										RenderInventory();

private:
	sf::RenderWindow							mGameWindow;
	System& mSystem;
	void										RenderParticles(std::vector<std::unique_ptr<Particle>>& particles);
	void										RenderChests(std::vector<std::unique_ptr<Chest>>& chests);
	void										RenderItems(std::vector<std::unique_ptr<Item>>& items);
};