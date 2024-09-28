#pragma once
#include "Assets.h"
#include <array>
#include <utility>
#include "MathUtilities.h"

namespace ITEMGEN
{
	static const std::vector<float> RarityProbabilities = { 0.500, 0.200, 0.150, 0.025, 0.015, 0.010, 0.100 };
	static const std::vector<float> RuneProbabilities =
	{
		0.031, // 1 : ELRUNE
		0.030, // 2 : ELDRUNE
		0.030, // 3 : TIRRUNE
		0.030, // 4 : NEFRUNE
		0.030, // 5 : ETHRUNE
		0.030, // 6 : ITHRUNE
		0.030, // 7 : TALRUNE
		0.030, // 8 : RALRUNE
		0.030, // 9 : ORTRUNE
		0.030, // 10: THULRUNE
		0.030, // 11: AMNRUNE
		0.030, // 12: SOLRUNE
		0.030, // 13: SHAELRUNE
		0.030, // 14: DOLRUNE
		0.030, // 15: HELRUNE
		0.030, // 16: IORUNE
		0.030, // 17: LUMRUNE
		0.030, // 18: KORUNE
		0.030, // 19: FALRUNE
		0.030, // 20: LEMRUNE
		0.030, // 21: PULRUNE
		0.030, // 22: UMRUNE
		0.030, // 23: MALRUNE
		0.030, // 24: ISTRUNE
		0.030, // 25: GULRUNE
		0.030, // 26: VEXRUNE
		0.030, // 27: OHMRUNE
		0.030, // 28: LORUNE
		0.030, // 29: SURRUNE
		0.030, // 30: BERRUNE
		0.030, // 31: JAHRUNE
		0.030, // 32: CHAMRUNE
		0.030, // 33: ZODRUNE
	};

	static const std::array<ITEMID::ITEM, 11> RarityNormalItems
	{
		ITEMID::REJUV_POTION,
		ITEMID::FULL_REJUV_POTION,
		ITEMID::OIL_POTION,
		ITEMID::STAMINA_POTION,
		ITEMID::SUPER_HEALING_POTION,
		ITEMID::SUPER_MANA_POTION,
		ITEMID::THAWING_POTION,
		ITEMID::RANCIDGAS_POTION,
		ITEMID::TPSCROLL,
		ITEMID::IDSCROLL,
	};

	static const std::array<ITEMID::ITEM, 9> RarityMagicItems
	{
		ITEMID::AMULET1,
		ITEMID::AMULET2,
		ITEMID::AMULET3,
		ITEMID::RING1,
		ITEMID::RING2,
		ITEMID::RING3,
		ITEMID::CHARM1,
		ITEMID::CHARM2,
		ITEMID::CHARM3,
	};

	static const std::array<ITEMID::ITEM, 13> RarityRareItems
	{
		ITEMID::AMULET1,
		ITEMID::AMULET2,
		ITEMID::AMULET3,
		ITEMID::RING1,
		ITEMID::RING2,
		ITEMID::RING3,
		ITEMID::AMETHYST_P,
		ITEMID::DIAMOND_P,
		ITEMID::EMERALD_P,
		ITEMID::RUBY_P,
		ITEMID::SAPPHIRE_P,
		ITEMID::TOPAZ_P,
		ITEMID::SKULL_P

	};

	static const std::array<ITEMID::ITEM, 6> RaritySetItems
	{
		ITEMID::AMULET1,
		ITEMID::AMULET2,
		ITEMID::AMULET3,
		ITEMID::RING1,
		ITEMID::RING2,
		ITEMID::RING3
	};

	static const std::array<ITEMID::ITEM, 6> RarityUniqueItems
	{
		ITEMID::AMULET1,
		ITEMID::AMULET2,
		ITEMID::AMULET3,
		ITEMID::RING1,
		ITEMID::RING2,
		ITEMID::RING3
	};

	static const std::array<ITEMID::ITEM, 33> RarityRuneItems
	{
		ITEMID::ELRUNE,
		ITEMID::ELDRUNE,
		ITEMID::TIRRUNE,
		ITEMID::NEFRUNE,
		ITEMID::ETHRUNE,
		ITEMID::ITHRUNE,
		ITEMID::TALRUNE,
		ITEMID::RALRUNE,
		ITEMID::ORTRUNE,
		ITEMID::THULRUNE,
		ITEMID::AMNRUNE,
		ITEMID::SOLRUNE,
		ITEMID::SHAELRUNE,
		ITEMID::DOLRUNE,
		ITEMID::HELRUNE,
		ITEMID::IORUNE,
		ITEMID::LUMRUNE,
		ITEMID::KORUNE,
		ITEMID::FALRUNE,
		ITEMID::LEMRUNE,
		ITEMID::PULRUNE,
		ITEMID::UMRUNE,
		ITEMID::MALRUNE,
		ITEMID::ISTRUNE,
		ITEMID::GULRUNE,
		ITEMID::VEXRUNE,
		ITEMID::OHMRUNE,
		ITEMID::LORUNE,
		ITEMID::SURRUNE,
		ITEMID::BERRUNE,
		ITEMID::JAHRUNE,
		ITEMID::CHAMRUNE,
		ITEMID::ZODRUNE
	};

	inline const std::array<int, ITEMID::MAX_ITEMS> ItemBaseValues
	{
		1,//GOLD,
		1000,//AMULET,
		2500,//CHARM,
		200,//REJUV,
		3000,//RING,
		5000,//RUNE1,
		300//TPSCROLL
	};

	static int getValueForItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item)
	{
		int baseValue = ItemBaseValues[item.first];
		int multiplier = item.second + 1;
		return baseValue * multiplier;
	}

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

	inline const int TOTAL_UNIQUE_ITEMS = {
		RarityNormalItems.size() + RarityMagicItems.size() + RarityRareItems.size()
		+ RaritySetItems.size() + RarityUniqueItems.size() + RarityRuneItems.size()
	};

	static ITEMRARITY::RARITY getRandomRarity()
	{
		ITEMRARITY::RARITY rarity = (ITEMRARITY::RARITY)MathU::DiscreteProbability(RarityProbabilities);
		return rarity;
	}

	static std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> getRandomItem()
	{
		ITEMRARITY::RARITY rarity = getRandomRarity();
		if (rarity == ITEMRARITY::GOLD)
		{
			return { ITEMID::GOLD, ITEMRARITY::GOLD };
		}
		if (rarity == ITEMRARITY::RUNE)
		{
			int runeIndex = MathU::DiscreteProbability(RuneProbabilities);
			ITEMID::ITEM rune = RarityRuneItems[runeIndex];
			return { rune, rarity };
		}
		ITEMID::ITEM item = getItemOfRarity(rarity);
		return { item, rarity };
	}

	static int getRandomGoldAmount()
	{
		return MathU::Random(1, 1000);
	}

}