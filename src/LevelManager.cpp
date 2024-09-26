#include "LevelManager.h"
#include <cassert>
#include "SystemManager.h"

LevelManager::LevelManager(System& system)
	:mSystem{system}
	,mCurrentLevel{ (LEVELS::LEVEL)(LEVELS::MAX_LEVELS - 1)}
{
	mLevels.reserve(LEVELS::MAX_LEVELS);
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_ONE, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_TWO, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_THREE, mSystem));
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 500.f, 300.f }, true);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 700.f, 800.f }, false);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 800.f, 400.f }, false);
	assert(mLevels.size() == LEVELS::MAX_LEVELS && "LevelManager did not make the right number of levels!");
}

Level& LevelManager::GetNextLevel()
{
	mCurrentLevel = (LEVELS::LEVEL)((mCurrentLevel + 1) % LEVELS::MAX_LEVELS);
	return *mLevels[mCurrentLevel];
}
