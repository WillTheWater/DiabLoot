#pragma once

namespace TEXTURES
{
	enum TEXTURE
	{
		MAINMENU,
		BUTTON,
		CHESTCLOSED,
		CHESTOPENED,
		MAP_ONE,
		AMULET,
		CHARM,
		REJUV,
		RING,
		RUNE1,
		TPSCROLL,
		PARTICLE,
		MAX_TEXTURES
	};
}

namespace SPRITES
{
	enum SPRITE
	{
		MAINMENU,
		BUTTON,
		CHESTCLOSED,
		CHESTOPENED,
		MAP_ONE,
		AMULET,
		CHARM,
		REJUV,
		RING,
		RUNE1,
		TPSCROLL,
		PARTICLE,
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

namespace LEVELS
{
	enum LEVEL
	{
		LEVEL_ONE,
		MAX_LEVELS
	};
}

namespace ITEMID
{
	enum ITEM
	{
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