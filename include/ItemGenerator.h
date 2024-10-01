#pragma once
#include "Assets.h"
#include <array>
#include <utility>
#include "MathUtilities.h"

namespace ITEMGEN
{
	static const std::vector<float> RarityProbabilities = { 0.509, 0.130, 0.093, 0.065, 0.073, 0.056, 0.075 }; // Gold, normal, magic, rare, set, unique, rune
	static const std::vector<float> RuneProbabilities =
	{
		0.030, // 1 : ELRUNE
		0.030, // 2 : ELDRUNE
		0.030, // 3 : TIRRUNE
		0.030, // 4 : NEFRUNE
		0.030, // 5 : ETHRUNE
		0.030, // 6 : ITHRUNE
		0.030, // 7 : TALRUNE
		0.030, // 8 : RALRUNE
		0.030, // 9 : ORTRUNE
		0.030, // 10: THULRUNE
		0.025, // 11: AMNRUNE
		0.022, // 12: SOLRUNE
		0.019, // 13: SHAELRUNE
		0.017, // 14: DOLRUNE
		0.015, // 15: HELRUNE
		0.013, // 16: IORUNE
		0.011, // 17: LUMRUNE
		0.009, // 18: KORUNE
		0.008, // 19: FALRUNE
		0.007, // 20: LEMRUNE
		0.006, // 21: PULRUNE
		0.0055, // 22: UMRUNE
		0.0050, // 23: MALRUNE
		0.0045, // 24: ISTRUNE
		0.0040, // 25: GULRUNE
		0.0035, // 26: VEXRUNE
		0.0030, // 27: OHMRUNE
		0.0027, // 28: LORUNE
		0.0024, // 29: SURRUNE
		0.0021, // 30: BERRUNE
		0.0019, // 31: JAHRUNE
		0.0017, // 32: CHAMRUNE
		0.0015, // 33: ZODRUNE
	};

	static const std::array<ITEMID::ITEM, 12> RarityNormalItems
	{
		ITEMID::KEY,
		ITEMID::REJUV_POTION,
		ITEMID::FULL_REJUV_POTION,
		ITEMID::OIL_POTION,
		ITEMID::STAMINA_POTION,
		ITEMID::SUPER_HEALING_POTION,
		ITEMID::SUPER_MANA_POTION,
		ITEMID::THAWING_POTION,
		ITEMID::RANCIDGAS_POTION,
		ITEMID::ANTIDOTE,
		ITEMID::TPSCROLL,
		ITEMID::IDSCROLL
	};

	static const std::array<ITEMID::ITEM, 15> RarityMagicItems
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
		ITEMID::JEWEL_1,
		ITEMID::JEWEL_2,
		ITEMID::JEWEL_3,
		ITEMID::JEWEL_4,
		ITEMID::JEWEL_5,
		ITEMID::JEWEL_6,
	};

	static const std::array<ITEMID::ITEM, 26> RarityRareItems
	{
		ITEMID::AMULET1,
		ITEMID::AMULET2,
		ITEMID::AMULET3,
		ITEMID::RING1,
		ITEMID::RING2,
		ITEMID::RING3,
		ITEMID::AMETHYST_P,
		ITEMID::AMETHYST_F,
		ITEMID::DIAMOND_P,
		ITEMID::DIAMOND_F,
		ITEMID::EMERALD_P,
		ITEMID::EMERALD_F,
		ITEMID::RUBY_P,
		ITEMID::RUBY_F,
		ITEMID::SAPPHIRE_P,
		ITEMID::SAPPHIRE_F,
		ITEMID::TOPAZ_P,
		ITEMID::TOPAZ_F,
		ITEMID::SKULL_P,
		ITEMID::SKULL_F,
		ITEMID::JEWEL_1,
		ITEMID::JEWEL_2,
		ITEMID::JEWEL_3,
		ITEMID::JEWEL_4,
		ITEMID::JEWEL_5,
		ITEMID::JEWEL_6,
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

	static const std::array<ITEMID::ITEM, 14> RarityUniqueItems
	{
		ITEMID::AMULET1,
		ITEMID::AMULET2,
		ITEMID::AMULET3,
		ITEMID::RING1,
		ITEMID::RING2,
		ITEMID::RING3,
		ITEMID::JEWEL_1,
		ITEMID::JEWEL_2,
		ITEMID::JEWEL_3,
		ITEMID::JEWEL_4,
		ITEMID::JEWEL_5,
		ITEMID::JEWEL_6,
		ITEMID::ANNIHILUS,
		ITEMID::WORLDSTONE_SHARD
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

	static int GetValueForItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item)
	{
		int baseValue = 100;
		int multiplier = (int)item.second;
		return (baseValue * multiplier);
	}

	static ITEMID::ITEM GetItemOfRarity(ITEMRARITY::RARITY rarity)
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

	static ITEMRARITY::RARITY GetRandomRarity()
	{
		ITEMRARITY::RARITY rarity = (ITEMRARITY::RARITY)MathU::DiscreteProbability(RarityProbabilities);
		return rarity;
	}

	static std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> GetRandomItem()
	{
		ITEMRARITY::RARITY rarity = GetRandomRarity();
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
		ITEMID::ITEM item = GetItemOfRarity(rarity);
		return { item, rarity };
	}

	static int GetRandomGoldAmount()
	{
		return MathU::Random(50, 1000);
	}

}