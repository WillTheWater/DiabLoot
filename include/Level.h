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
	void									RemoveParticle(Particle& particle);
	void									PickUpItem(Item& item);
	void									SpawnItem(Particle& particle);
	void									SortItemsByVerticalSpace();
	void									StackItemlabels();
	void									RemoveAllObservers();
	void									AddAllObservers();

private:
	LEVELS::LEVEL							mLevelID;
	std::vector<std::unique_ptr<Chest>>		mChests;
	std::vector<std::unique_ptr<Particle>>	mParticles;
	std::vector<std::unique_ptr<Item>>		mItems;
	System&									mSystem;
	int										mParticleUniqueId;
};