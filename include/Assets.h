#pragma once

namespace TEXTURES
{
	enum TEXTURE
	{
		MAINMENU,
		WIDE_BUTTON,
		SQUARE_BUTTON,
		INVENTORY,
		CHESTCLOSED,
		CHESTOPENED,
		MAP_ONE,
		MAP_TWO,
		MAP_THREE,
		MAP_FOUR,
		MAP_FIVE,
		MAP_SIX,
		MAP_SEVEN,
		MAP_EIGHT,
		MAP_NINE,
		MAP_TEN,
		AMULET1,
		AMULET2,
		AMULET3,
		CHARM1,
		CHARM2,
		CHARM3,
		REJUV_POTION,
		FULL_REJUV_POTION,
		ANTIDOTE,
		OIL_POTION,
		STAMINA_POTION,
		SUPER_HEALING_POTION,
		SUPER_MANA_POTION,
		THAWING_POTION,
		RANCIDGAS_POTION,
		AMETHYST_P,
		DIAMOND_P,
		EMERALD_P,
		RUBY_P,
		SAPPHIRE_P,
		TOPAZ_P,
		SKULL_P,
		RING1,
		RING2,
		RING3,
		TPSCROLL,
		IDSCROLL,

		PARTICLE,
		GOLD_SMALL,
		GOLD_MEDIUM,
		GOLD_LARGE,
		ELRUNE,
		ELDRUNE,
		TIRRUNE,
		NEFRUNE,
		ETHRUNE,
		ITHRUNE,
		TALRUNE,
		RALRUNE,
		ORTRUNE,
		THULRUNE,
		AMNRUNE,
		SOLRUNE,
		SHAELRUNE,
		DOLRUNE,
		HELRUNE,
		IORUNE,
		LUMRUNE,
		KORUNE,
		FALRUNE,
		LEMRUNE,
		PULRUNE,
		UMRUNE,
		MALRUNE,
		ISTRUNE,
		GULRUNE,
		VEXRUNE,
		OHMRUNE,
		LORUNE,
		SURRUNE,
		BERRUNE,
		JAHRUNE,
		CHAMRUNE,
		ZODRUNE,
		MAX_TEXTURES
	};
}

namespace SPRITES
{
	enum SPRITE
	{
		MAINMENU,
		WIDE_BUTTON,
		SQUARE_BUTTON,
		INVENTORY,
		CHESTCLOSED,
		CHESTOPENED,
		MAP_ONE,
		MAP_TWO,
		MAP_THREE,
		MAP_FOUR,
		MAP_FIVE,
		MAP_SIX,
		MAP_SEVEN,
		MAP_EIGHT,
		MAP_NINE,
		MAP_TEN,
		AMULET1,
		AMULET2,
		AMULET3,
		CHARM1,
		CHARM2,
		CHARM3,
		REJUV_POTION,
		FULL_REJUV_POTION,
		ANTIDOTE,
		OIL_POTION,
		STAMINA_POTION,
		SUPER_HEALING_POTION,
		SUPER_MANA_POTION,
		THAWING_POTION,
		RANCIDGAS_POTION,
		AMETHYST_P,
		DIAMOND_P,
		EMERALD_P,
		RUBY_P,
		SAPPHIRE_P,
		TOPAZ_P,
		SKULL_P,
		RING1,
		RING2,
		RING3,
		TPSCROLL,
		IDSCROLL,
		PARTICLE,
		GOLD_SMALL,
		GOLD_MEDIUM,
		GOLD_LARGE,
		ELRUNE,
		ELDRUNE,
		TIRRUNE,
		NEFRUNE,
		ETHRUNE,
		ITHRUNE,
		TALRUNE,
		RALRUNE,
		ORTRUNE,
		THULRUNE,
		AMNRUNE,
		SOLRUNE,
		SHAELRUNE,
		DOLRUNE,
		HELRUNE,
		IORUNE,
		LUMRUNE,
		KORUNE,
		FALRUNE,
		LEMRUNE,
		PULRUNE,
		UMRUNE,
		MALRUNE,
		ISTRUNE,
		GULRUNE,
		VEXRUNE,
		OHMRUNE,
		LORUNE,
		SURRUNE,
		BERRUNE,
		JAHRUNE,
		CHAMRUNE,
		ZODRUNE,
		MAX_SPRITES
	};

}

namespace FONTS
{
	enum FONT
	{
		BOLD,
		LIGHT,
		MAX_FONTS
	};

	inline float PADDING = 8.f;
	inline float ORIGIN_YOFFSET = -5.f;
}

namespace IMAGES
{
	enum IMAGE
	{
		DEFAULT_CURSOR,
		CLOSED_CURSOR,
		ICON,
		MAX_IMAGES
	};
}

namespace SOUNDBUFFERS
{
	enum SOUNDBUFFER
	{
		BUTTON_DOWN_SB,
		CHEST_OPEN_SB,
		MAX_SOUNDSBUFFERS
	};
}

namespace PLAYSOUND
{
	enum PLAYSOUND
	{
		BUTTON_DOWN,
		OPEN_CHEST,
		MAX_SOUNDS
	};
}

namespace MUSIC
{
	enum PLAYMUSIC
	{
		INTRO,
		TRISTRAM,
		MAX_MUSIC_FILES
	};
}

namespace CHANNELS
{
	enum CHANNEL
	{
		SFX,
		MUSIC,
		AMBIENT,
		MAX_CHANNELS
	};
}

namespace BUTTONS
{
	enum BUTTON_TEXT
	{
		START,
		LOAD_GAME,
		EXIT,
		NEXT_LEVEL,
		OPEN_INVENTORY,
		EXIT_PLAY,
		MAX_BUTTONS
	};
	enum BUTTON_TYPE
	{
		WIDE,
		SQUARE,
		MAX_TYPES
	};

	enum BUTTON_STATE
	{
		IDLE,
		HOVER,
		CLICK,
		MAX_STATES
	};

	enum BUTTON_ID
	{
		START_ID,
		LOAD_GAME_ID,
		EXIT_ID,
		NEXT_LEVEL_ID,
		INVENTORY_ID,
		OPEN_INVENTORY_ID,
		EXIT_PLAY_ID,
		MAX_BUTTONS_ID
	};
}

namespace LEVELS
{
	enum LEVEL
	{
		LEVEL_ONE,
		LEVEL_TWO,
		LEVEL_THREE,
		LEVEL_FOUR,
		LEVEL_FIVE,
		LEVEL_SIX,
		LEVEL_SEVEN,
		LEVEL_EIGHT,
		LEVEL_NINE,
		LEVEL_TEN,
		MAX_LEVELS
	};
}

namespace ITEMID
{
	enum ITEM
	{
		GOLD,
		AMULET1,
		AMULET2,
		AMULET3,
		CHARM1,
		CHARM2,
		CHARM3,
		REJUV_POTION,
		FULL_REJUV_POTION,
		ANTIDOTE,
		OIL_POTION,
		STAMINA_POTION,
		SUPER_HEALING_POTION,
		SUPER_MANA_POTION,
		THAWING_POTION,
		RANCIDGAS_POTION,
		AMETHYST_P,
		DIAMOND_P,
		EMERALD_P,
		RUBY_P,
		SAPPHIRE_P,
		TOPAZ_P,
		SKULL_P,
		RING1,
		RING2,
		RING3,
		TPSCROLL,
		IDSCROLL,
		ELRUNE,
		ELDRUNE,
		TIRRUNE,
		NEFRUNE,
		ETHRUNE,
		ITHRUNE,
		TALRUNE,
		RALRUNE,
		ORTRUNE,
		THULRUNE,
		AMNRUNE,
		SOLRUNE,
		SHAELRUNE,
		DOLRUNE,
		HELRUNE,
		IORUNE,
		LUMRUNE,
		KORUNE,
		FALRUNE,
		LEMRUNE,
		PULRUNE,
		UMRUNE,
		MALRUNE,
		ISTRUNE,
		GULRUNE,
		VEXRUNE,
		OHMRUNE,
		LORUNE,
		SURRUNE,
		BERRUNE,
		JAHRUNE,
		CHAMRUNE,
		ZODRUNE,
		MAX_ITEMS
	};
}

namespace ITEMRARITY
{
	enum RARITY
	{
		NORMAL,			// 0
		MAGIC,			// 1
		RARE,			// 2
		SET,			// 3
		UNIQUE,			// 4
		RUNE,			// 5
		MAX_RARITIES	// 6
	};
}

namespace PARTICLE
{
	inline float ANIMSTEP = 2.0f;
}