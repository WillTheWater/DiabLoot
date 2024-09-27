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
		AMULET,
		CHARM,
		REJUV,
		RING,
		RUNE1,
		TPSCROLL,
		PARTICLE,
		GOLD_SMALL,
		GOLD_MEDIUM,
		GOLD_LARGE,
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
		AMULET,
		CHARM,
		REJUV,
		RING,
		RUNE1,
		TPSCROLL,
		PARTICLE,
		GOLD_SMALL,
		GOLD_MEDIUM,
		GOLD_LARGE,
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

namespace SOUNDS
{
	enum SOUND
	{
		BUTTON,
		MAX_SOUNDS
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
		EXIT,
		NEXT_LEVEL,
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
}

namespace LEVELS
{
	enum LEVEL
	{
		LEVEL_ONE,
		LEVEL_TWO,
		LEVEL_THREE,
		MAX_LEVELS
	};
}

namespace ITEMID
{
	enum ITEM
	{
		GOLD,
		AMULET,
		CHARM,
		REJUV,
		RING,
		RUNE1,
		TPSCROLL,
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