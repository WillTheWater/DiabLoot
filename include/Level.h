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
#include <list>

class System;

class Level
{
public:
	Level() = delete;
	Level(LEVELS::LEVEL id, System& system);
	~Level();

	std::array<std::unique_ptr<Chest>, 4>&	GetChests();
	std::list<std::unique_ptr<Particle>>&	GetParticles();
	std::list<std::unique_ptr<Item>>&		GetItems();
	LEVELS::LEVEL							GetLevelId() const;
	void									EnterLevel();
	void									ExitLevel();
	void									UpdateLevel();
	void									UpdateParticles();
	void									UpdateItems();
	int										GetUniqueParticleId();
	void									SpawnChest(sf::Vector2f pos, bool mirrored, LEVELS::UPGRADE chest);
	void									SpawnParticles(Chest& chest);
	void									CreateBounceParticle(Item& item);
	void									UpgradeLevel();
	LEVELS::UPGRADE							GetUpgradeLevel();
	void									SetUpgradeLevel(LEVELS::UPGRADE upgrade); // Only used for loading
	void									ActivateChests(); //Turns on the relevant chests for upgrade level and also adds them as observers;
	void									DeactiveChests();
	void									ResetLevelUpgrades();
	void									SetRain(bool rain);
	bool									HasRain();
	bool									ThunderStrike();

private:
	LEVELS::LEVEL							mLevelID;
	std::array<std::unique_ptr<Chest>, 4>	mChests;
	std::list<std::unique_ptr<Particle>>	mParticles;
	std::list<std::unique_ptr<Item>>		mItems;
	System&									mSystem;
	int										mParticleUniqueId;
	LEVELS::UPGRADE							mUpgradeLevel;
	std::vector<int>						mParticlesToRemove;
	std::vector<int>						mItemsToRemove;
	bool									mRain;
	bool									mThunder;
	// Private Functions
	void									RemoveOldParticles();
	void									RemoveOldItems();
	void									SetParticleForRemoval(Particle& particle);
	void									SetItemForRemoval(Item& item);
	void									PickUpItem(Item& item);
	void									SpawnItem(Particle& particle);
	void									TurnItemToGold(Particle& particle);
	void									SortItemsByVerticalSpace();
	void									StackItemlabels();
	void									RemoveAllChestObservers();
	void									RemoveAllItemObsevers();
	void									RandomThunder();
};