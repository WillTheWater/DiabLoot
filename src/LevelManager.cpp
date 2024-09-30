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
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 555.f, 250.f }, true);
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 1400.f, 725.f }, false);
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 750.f, 365.f }, false);	
	mLevels[LEVELS::LEVEL_ONE]->SpawnChest({ 900.f, 525.f }, false);
	// Level Two Chests
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 530.f, 700.f }, true);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 1250.f, 300.f }, false);
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 1050.f, 400.f }, false);	
	mLevels[LEVELS::LEVEL_TWO]->SpawnChest({ 850.f, 200.f }, false);
	// Level Three Chests
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 200.f, 980.f }, true);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 1170.f, 170.f }, true);
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 870.f, 370.f }, true);	
	mLevels[LEVELS::LEVEL_THREE]->SpawnChest({ 570.f, 570.f }, true);	
	// Level Four Chests
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 1170.f, 560.f }, false);
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 870.f, 860.f }, false);	
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 670.f, 660.f }, false);	
	mLevels[LEVELS::LEVEL_FOUR]->SpawnChest({ 280.f, 260.f }, false);
	// Level Five Chests
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 1200.f, 920.f }, false);
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 1120.f, 430.f }, true);
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 800.f, 830.f }, true);	
	mLevels[LEVELS::LEVEL_FIVE]->SpawnChest({ 560.f, 560.f }, true);	
	// Level Six Chests
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 520.f, 320.f }, true);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 820.f, 470.f }, false);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 1650.f, 980.f }, true);
	mLevels[LEVELS::LEVEL_SIX]->SpawnChest({ 950.f, 580.f }, true);		
	// Level Seven Chests
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 1000.f, 180.f }, true);
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 600.f, 800.f }, false);
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 800.f, 900.f }, false);	
	mLevels[LEVELS::LEVEL_SEVEN]->SpawnChest({ 500.f, 500.f }, false);	
	// Level Eight Chests
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 1330.f, 340.f }, false); 
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 930.f, 440.f }, false);	
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 1030.f, 740.f }, false); 
	mLevels[LEVELS::LEVEL_EIGHT]->SpawnChest({ 530.f, 540.f }, false);	
	// Level Nine Chests
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 340.f, 330.f }, true);
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 1450.f, 320.f }, false);
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 950.f, 520.f }, false);	
	mLevels[LEVELS::LEVEL_NINE]->SpawnChest({ 1050.f, 1020.f }, false);
	// Level Ten Chests
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 1180.f, 480.f }, false);
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 600.f, 350.f }, true);
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 900.f, 550.f }, true);		
	mLevels[LEVELS::LEVEL_TEN]->SpawnChest({ 750.f, 750.f }, true);		
	// Level Eleven Chests
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 1180.f, 480.f }, false);
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 600.f, 350.f }, true);
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 900.f, 550.f }, true);		
	mLevels[LEVELS::LEVEL_ELEVEN]->SpawnChest({ 750.f, 750.f }, true);	
	// Level Twelve Chests
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 1180.f, 480.f }, false);
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 600.f, 350.f }, true);
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 900.f, 550.f }, true);		
	mLevels[LEVELS::LEVEL_TWELVE]->SpawnChest({ 750.f, 750.f }, true);	
	// Level Thirteen Chests
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 1180.f, 480.f }, false);
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 600.f, 350.f }, true);
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 900.f, 550.f }, true);		
	mLevels[LEVELS::LEVEL_THIRTEEN]->SpawnChest({ 750.f, 750.f }, true);		

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
	outData.open("levelData.lvl");
	assert(outData && "LevelManager::SaveLevels failed to open inventoryData.inv file");
	outData << "#UPGRADES\n";
	for (int i{ 0 }; i < mLevels.size(); i++)
	{
		outData << mLevels[i]->GetUpgradeLevel() << '\n';
	}
	outData.close();
}

void LevelManager::LoadLevels()
{
	std::ifstream inData("levelData.lvl");
	assert(inData && "LevelManager::LoadLevels failed to open inventoryData.inv file");
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
}

void LevelManager::ResetLevelUpgrades()
{
	for (auto& level : mLevels)
	{
		level->ResetLevelUpgrades();t
	}
}
