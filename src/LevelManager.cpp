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
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_ELEVEN, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_TWELVE, mSystem));
	mLevels.push_back(std::make_unique<Level>(LEVELS::LEVEL_THIRTEEN, mSystem));
	// Level One Chests
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 1136.f, 270.f }, true, 1);
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 660.f, 236.f }, true, 2);
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 432.f, 640.f }, false, 3);	
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 1734.f, 654.f }, false, 4);
	// Level Two Chests
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 1158.f, 428.f }, false, 1);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 636.f, 228.f }, true, 2);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 1686.f, 754.f }, false, 3);	
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 470.f, 698.f }, true, 4);
	// Level Three Chests
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 1360.f, 362.f }, false, 1);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 736.f, 214.f }, true, 2);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 1650.f, 572.f }, false, 3);	
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 412.f, 706.f }, true, 4);	
	// Level Four Chests
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 680.f, 494.f }, true, 1);
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 1284.f, 278.f }, false, 2);	
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 252.f, 694.f }, false, 3);	
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 1568.f, 320.f }, true, 4);
	// Level Five Chests
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 402.f, 252.f }, false, 1);
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 1130.f, 712.f }, true, 2);
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 806.f, 710.f }, false, 3);	
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 1346.f, 302.f }, false, 4);	
	// Level Six Chests
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 1370.f, 388.f }, false, 1);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 434.f, 358.f }, true, 2);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 1484.f, 676.f }, false, 3);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 394.f, 726.f }, true, 4);		
	// Level Seven Chests
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 1532.f, 332.f }, true, 1);
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 776.f, 306.f }, false, 2);
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 1226.f, 514.f }, true, 3);	
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 1038.f, 532.f }, false, 4);	
	// Level Eight Chests
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 1520.f, 812.f }, false, 1); 
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 278.f, 380.f }, true, 2);	
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 1508.f, 128.f }, true, 3); 
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 1184.f, 372.f }, true, 4);	
	// Level Nine Chests
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 1236.f, 656.f }, true, 1);
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 964.f, 182.f }, true, 2);
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 352.f, 486.f }, true, 3);	
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 856.f, 470.f }, true, 4);
	// Level Ten Chests
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 498.f, 186.f }, true, 1);
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 660.f, 642.f }, true, 2);
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 1384.f, 334.f }, false, 3);		
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 1312.f, 690.f }, true, 4);		
	// Level Eleven Chests
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 1036.f, 524.f }, false, 1);
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 788.f, 276.f }, true, 2);
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 1536.f, 658.f }, false, 3);		
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 532.f, 794.f }, false, 4);	
	// Level Twelve Chests
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 1092.f, 290.f }, false, 1);
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 472.f, 622.f }, false, 2);
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 988.f, 526.f }, true, 3);		
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 442.f, 276.f }, true, 4);	
	// Level Thirteen Chests
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 634.f, 706.f }, false, 1);
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 1240.f, 338.f }, false, 2);
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 1476.f, 458.f }, false, 3);		
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 588.f, 276.f }, true, 4);		

	assert(mLevels.size() == LEVELS::MAX_LEVELS && "LevelManager did not make the right number of levels!");
}

Level& LevelManager::GetNextLevel()
{
	mCurrentLevel = (LEVELS::LEVEL)((mCurrentLevel + 1) % LEVELS::MAX_LEVELS);
	return *mLevels[mCurrentLevel];
}

void LevelManager::SaveLevels()
{
	std::ofstream outData;
	// Save the file in the save directory created by CMake
	std::string filePath = "save/levelData.lvl";  // Relative path
	outData.open(filePath);
	assert(outData && "LevelManager::SaveLevels failed to open levelData.lvl file");

	outData << "#UPGRADES\n";
	for (int i{ 0 }; i < mLevels.size(); i++)
	{
		outData << mLevels[i]->GetUpgradeLevel() << '\n';
	}
	outData.close();
}

void LevelManager::LoadLevels()
{
	std::ifstream inData("save/levelData.lvl");  // Relative path to the save directory
	assert(inData && "LevelManager::LoadLevels failed to open levelData.lvl file");

	std::string line;
	while (std::getline(inData, line))
	{
		if (line == "#UPGRADES")
		{
			int index = 0;
			while (index < mLevels.size())
			{
				std::getline(inData, line);
				int upgrade = std::stoi(line);
				// std::cout << "Level " << index << " Upgrade: " << upgrade << '\n'; // DEBUG
				mLevels[index]->SetUpgradeLevel((LEVELS::UPGRADE)upgrade);
				index++;
			}
			break;
		}
	}
	inData.close();
}

void LevelManager::ResetLevelUpgrades()
{
	for (auto& level : mLevels)
	{
		level->ResetLevelUpgrades();
	}
}

void LevelManager::ResetLevelLoop()
{
	mCurrentLevel = (LEVELS::LEVEL)(LEVELS::MAX_LEVELS - 1);
}

Level& LevelManager::GetCurrentLevel()
{
	return *mLevels[(size_t)mCurrentLevel];
}
