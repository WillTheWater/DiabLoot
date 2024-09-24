#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <functional>
#include "AssetManager.h"
#include "GUIManager.h"
#include "Level.h"
#include "Item.h"
#include "Inventory.h"

class RenderManager
{
public:
	RenderManager(GUIManager& guiMgr);

	sf::RenderWindow&							GetWindow();
	void									    MainMenuRender();
	void										DrawButtons();
	void										RenderLevel(Level& level);
	void										RenderInventory(Inventory& inventory);

	template <typename T>
	void										Draw(const T& drawObject) { mGameWindow.draw(drawObject); }
	sf::Text&									GetTextForItemId(ITEMID::ITEM item);

private:
	AssetManager								mAssetMgr;
	GUIManager&									mGUIMgr;
	sf::RenderWindow							mGameWindow;
	void										RenderParticles(std::vector<std::unique_ptr<Particle>>& particles);
	void										RenderChests(std::vector<std::unique_ptr<Chest>>& chests);
	void										RenderItems(std::vector<std::unique_ptr<Item>>& items);
};