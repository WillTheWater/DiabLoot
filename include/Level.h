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
#include "SoundManager.h"
#include <utility>
#include <algorithm>

class System;

class Level
{
public:
	Level() = delete;
	Level(LEVELS::LEVEL id, System& system);
	~Level();

	std::vector<std::unique_ptr<Chest>>&	GetChests();
	std::vector<std::unique_ptr<Particle>>&	GetParticles();
	std::vector<std::unique_ptr<Item>>&		GetItems();
	LEVELS::LEVEL							GetLevelId() const;
	void									EnterLevel();
	void									ExitLevel();
	void									UpdateLevel();
	void									UpdateParticles();
	void									UpdateItems();
	int										GetUniqueParticleId();
	void									SpawnChest(sf::Vector2f pos, bool mirrored);
	void									SpawnParticles(Chest& chest);
	void									CreateBounceParticle(Item& item);
	void									RemoveParticle(Particle& particle);
	void									PickUpItem(Item& item);
	void									SpawnItem(Particle& particle);
	void									TurnItemToGold(Particle& particle);
	void									SortItemsByVerticalSpace();
	void									StackItemlabels();
	void									RemoveAllItemObservers();
	void									AddAllItemObservers();
	void									RemoveAllChestObservers();

	void									UpgradeLevel();
	LEVELS::UPGRADE							GetUpgradeLevel();
	void									SetUpgradeLevel(LEVELS::UPGRADE upgrade); // Only used for loading
	void									ActivateChests(); //Turns on the relevant chests for upgrade level and also adds them as observers;
	void									DeactiveChests();
	void									ResetLevelUpgrades();

private:
	LEVELS::LEVEL							mLevelID;
	std::vector<std::unique_ptr<Chest>>		mChests;
	std::vector<std::unique_ptr<Particle>>	mParticles;
	std::vector<std::unique_ptr<Item>>		mItems;
	System&									mSystem;
	int										mParticleUniqueId;
	LEVELS::UPGRADE							mUpgradeLevel;
};