#pragma once
#include "Level.h"
#include "Assets.h"
#include <vector>

class System;

class LevelManager
{
public:
	LevelManager() = delete;
	LevelManager(System& system);

	Level&				GetNextLevel();
	void				SaveLevels();
	void				LoadLevels();
	void				ResetLevelUpgrades();
	void				ResetLevelLoop();
	Level&				GetCurrentLevel();



private:
	System&										mSystem;
	std::vector<std::unique_ptr<Level>>			mLevels;
	LEVELS::LEVEL								mCurrentLevel;
};