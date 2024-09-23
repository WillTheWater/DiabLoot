#pragma once
#include "Assets.h"
#include <array>
#include <utility>

namespace ITEMGEN
{

	static const std::array<ITEMID::ITEM, 1> RarityNoneItems
	{
		ITEMID::GOLD
	};

	static const std::array<ITEMID::ITEM, 1> RarityNormalItems
	{
		ITEMID::GOLD
	};

	static const std::array<ITEMID::ITEM, 1> RarityMagicItems
	{
		ITEMID::GOLD
	};

	static const std::array<ITEMID::ITEM, 1> RarityRareItems
	{
		ITEMID::GOLD
	};

	static const std::array<ITEMID::ITEM, 1> RaritySetItems
	{
		ITEMID::GOLD
	};

	static const std::array<ITEMID::ITEM, 1> RarityUniqueItems
	{
		ITEMID::GOLD
	};

	static std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> getRandomItem()
	{

	}

	static ITEMID::ITEM getItemOfRarity(ITEMRARITY::RARITY rarity)
	{

	}

	static ITEMRARITY::RARITY getRandomRarity()
	{

	}

}