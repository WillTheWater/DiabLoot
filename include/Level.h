#pragma once

#include "Chest.h"
#include "Particle.h"
#include "MathUtilities.h"
#include "Vec2.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Assets.h"
#include <cassert>
#include "Item.h"
#include "ItemGenerator.h"
#include <utility>
#include <algorithm>

class Level
{
public:
	Level() = delete;
	Level(LEVELS::LEVEL id, TimeManager& timemgr, InputManager& inputmgr, std::function<sf::Text& (ITEMID::ITEM)> itemTextCB);
	~Level();

	std::vector<std::unique_ptr<Chest>>&	GetChests();
	std::vector<std::unique_ptr<Particle>>&	GetParticles();

	std::vector<std::unique_ptr<Item>>&		GetItems();
	LEVELS::LEVEL							GetLevelId() const;


	void									UpdateLevel();
	void									UpdateParticles();
	void									UpdateItems();
	void									CreateLevelChests();
	int										GetUniqueParticleId();
	void									SpawnChest(sf::Vector2f pos, bool mirrored);
	void									SpawnParticles(Chest& chest);
	void									RemoveParticle(Particle& particle);
	void									PickUpItem(Item& item);
	void									SpawnItem(Particle& particle);
	void									SortItemsByVerticalSpace();
	void									StackItemlabels();

private:
	LEVELS::LEVEL							mLevelID;
	TimeManager&							mTimeManager;
	InputManager&							mInputManager;
	int										mParticleUniqueId;
	std::vector<std::unique_ptr<Chest>>		mChests;
	std::vector<std::unique_ptr<Particle>>	mParticles;
	std::vector<std::unique_ptr<Item>>		mItems;
	std::function<sf::Text& (ITEMID::ITEM)> mItemTextCB;
};