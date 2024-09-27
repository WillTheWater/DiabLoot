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
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_FOUR, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_FIVE, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_SIX, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_SEVEN, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_EIGHT, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_NINE, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_TEN, mSystem));

	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 555.f, 250.f }, true);
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 1400.f, 725.f }, false);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 530.f, 700.f }, true);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 1250.f, 300.f }, false);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 200.f, 980.f }, true);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 1170.f, 170.f }, true);
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 1170.f, 560.f }, false);
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 1200.f, 920.f }, false);
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 1120.f, 430.f }, true);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 520.f, 320.f }, true);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 820.f, 470.f }, false);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 1650.f, 980.f }, true);
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 1000.f, 180.f }, true);
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 600.f, 800.f }, false);
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 1330.f, 340.f }, false); // Fix this one later
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 340.f, 330.f }, true);
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 1450.f, 320.f }, false);
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 1180.f, 480.f }, false);
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 600.f, 350.f }, true);
	assert(mLevels.size() == LEVELS::MAX_LEVELS && "LevelManager did not make the right number of levels!");
}

Level& LevelManager::GetNextLevel()
{
	mCurrentLevel = (LEVELS::LEVEL)((mCurrentLevel + 1) % LEVELS::MAX_LEVELS);
	return *mLevels[mCurrentLevel];
}
