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
		GOLD,
		MAX_ITEMS
	};
}

namespace ITEMRARITY
{
	enum RARITY
	{
		NONE,			// 0
		NORMAL,			// 1
		MAGIC,			// 2
		RARE,			// 3
		SET,			// 4
		UNIQUE,			// 5
		MAX_RARITIES	// 6
	};
}