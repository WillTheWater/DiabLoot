#pragma once
#include "Assets.h"
#include <array>
#include <utility>
#include "MathUtilities.h"

namespace ITEMGEN
{
	static const std::vector<float> RarityProbabilities = { 0.700, 0.150, 0.025, 0.015, 0.010, 0.100 };

	static const std::array<ITEMID::ITEM, 2> RarityNormalItems
	{
		ITEMID::REJUV,
		ITEMID::TPSCROLL
	};

	static const std::array<ITEMID::ITEM, 3> RarityMagicItems
	{
		ITEMID::AMULET,
		ITEMID::RING,
		ITEMID::CHARM
	};

	static const std::array<ITEMID::ITEM, 2> RarityRareItems
	{
		ITEMID::AMULET,
		ITEMID::RING
	};

	static const std::array<ITEMID::ITEM, 2> RaritySetItems
	{
		ITEMID::AMULET,
		ITEMID::RING
	};

	static const std::array<ITEMID::ITEM, 2> RarityUniqueItems
	{
		ITEMID::AMULET,
		ITEMID::RING
	};

	static const std::array<ITEMID::ITEM, 1> RarityRuneItems
	{
		ITEMID::RUNE1
	};

	static ITEMID::ITEM getItemOfRarity(ITEMRARITY::RARITY rarity)
	{
		int randomIndex;
		switch (rarity)
		{
		case ITEMRARITY::NORMAL :	
			randomIndex = MathU::Random(0, (int)RarityNormalItems.size() - 1);
			return RarityNormalItems[randomIndex];

		case ITEMRARITY::MAGIC	:
			randomIndex = MathU::Random(0, (int)RarityMagicItems.size() - 1);
			return RarityMagicItems[randomIndex];

		case ITEMRARITY::RARE	:
			randomIndex = MathU::Random(0, (int)RarityRareItems.size() - 1);
			return RarityRareItems[randomIndex];

		case ITEMRARITY::SET	:
			randomIndex = MathU::Random(0, (int)RaritySetItems.size() - 1);
			return RaritySetItems[randomIndex];

		case ITEMRARITY::UNIQUE :
			randomIndex = MathU::Random(0, (int)RarityUniqueItems.size() - 1);
			return RarityUniqueItems[randomIndex];

		case ITEMRARITY::RUNE   :
			randomIndex = MathU::Random(0, (int)RarityRuneItems.size() - 1);
			return RarityRuneItems[randomIndex];

		default : 
			randomIndex = MathU::Random(0, (int)RarityNormalItems.size() - 1);
			return RarityNormalItems[randomIndex];

		}
	}

	static ITEMRARITY::RARITY getRandomRarity()
	{
		ITEMRARITY::RARITY rarity = (ITEMRARITY::RARITY)MathU::DiscreteProbability(RarityProbabilities);
		return rarity;
	}

	static std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> getRandomItem()
	{
		ITEMRARITY::RARITY rarity = getRandomRarity();
		ITEMID::ITEM item = getItemOfRarity(rarity);
		return { item, rarity };
	}

}