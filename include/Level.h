#pragma once

#include "Chest.h"
#include "Particle.h"
#include "MathUtilities.h"
#include "Vec2.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Assets.h"
#include <cassert>

class Level
{
public:
	Level() = delete;
	Level(LEVELS::LEVEL id, TimeManager& timemgr, InputManager& inputmgr);
	~Level();

	std::vector<std::unique_ptr<Chest>>&	GetChests();
	std::vector<std::unique_ptr<Particle>>&	GetParticles();
	LEVELS::LEVEL							GetLevelId();

	void									UpdateLevel();
	void									CreateLevelChests();
	int										GetUniqueParticleId();
	void									SpawnChest(sf::Vector2f pos, bool mirrored);
	void									SpawnParticles(Chest& chest);
	void									UpdateParticles();
	void									RemoveParticle(Particle& particle);
	void									SpawnItem(Particle& particle);

private:
	LEVELS::LEVEL							mLevelID;
	TimeManager&							mTimeManager;
	InputManager&							mInputManager;
	int										mParticleUniqueId;
	std::vector<std::unique_ptr<Chest>>		mChests;
	std::vector<std::unique_ptr<Particle>>	mParticles;
};