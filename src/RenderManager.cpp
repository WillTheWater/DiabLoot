#include "RenderManager.h"
#include "SystemManager.h"
#include "Core.h"
#include <iostream>
#include <sstream>
#include <string>

RenderManager::RenderManager(System& system)
	: mGameWindow{ sf::VideoMode(1920u, 1080u), "DiabLoot", sf::Style::None, sf::ContextSettings(0,0,8)}
	, mSystem{ system }
	, mWindowCenter{ mGameWindow.getSize().x / 2.f, mGameWindow.getSize().y / 2.f }
{
	mGameWindow.setFramerateLimit(60);
}

sf::RenderWindow& RenderManager::GetWindow()
{
	return mGameWindow;
}

sf::Cursor& RenderManager::GetDefaultCursor()
{
	return mCursorOpen;
}

sf::Cursor& RenderManager::GetClosedCursor()
{
	return mCursorClosed;
}

void RenderManager::CustomizeGameWindow()
{
	// Cursor
	auto& defaultCursor = mSystem.AssetMgr.GetImage(IMAGES::DEFAULT_CURSOR);
	auto& closedCursor = mSystem.AssetMgr.GetImage(IMAGES::CLOSED_CURSOR);
	mCursorOpen.loadFromPixels(defaultCursor.getPixelsPtr(), defaultCursor.getSize(), { 0, 0 });
	mCursorClosed.loadFromPixels(closedCursor.getPixelsPtr(), closedCursor.getSize(), { 0, 0 });
	mGameWindow.setMouseCursor(mCursorOpen);

	// Window icon
	auto& widnowIcon = mSystem.AssetMgr.GetImage(IMAGES::ICON);
	mGameWindow.setIcon(widnowIcon.getSize().x, widnowIcon.getSize().y, widnowIcon.getPixelsPtr());
}

void RenderManager::MainMenuRender()
{

	Draw(mSystem.AssetMgr.GetSprite(SPRITES::MAINMENU));
	mSystem.TimeMgr.UpdateFireFrame();
	Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1460.f, 536.f }, 0.3f));
	Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 330.f, 530.f }, 0.3f));
	Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1560.f, 566.f }, 0.3f));
	Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 361.f, 366.f }, 2.1f));
	Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 461.f, 366.f }, 1.8f));
	Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 561.f, 366.f }, 2.3f));
	Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 671.f, 296.f }, 1.8f));
	Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 791.f, 366.f }, 2.6f));
	Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 991.f, 296.f }, 2.8f));
	Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 1091.f, 366.f }, 2.4f));
	Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1211.f, 296.f }, 2.5f));
	Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 1391.f, 366.f }, 2.8f));
	Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 1491.f, 366.f }, 2.3f));
	Draw(mSystem.AssetMgr.GetSprite(SPRITES::MAINMENUTITLE));


	Draw(mSystem.GUIMgr.GetButton(BUTTONS::START_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::START_ID).GetText());

	Draw(mSystem.GUIMgr.GetButton(BUTTONS::LOAD_GAME_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::LOAD_GAME_ID).GetText());

	Draw(mSystem.GUIMgr.GetButton(BUTTONS::EXIT_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::EXIT_ID).GetText());

	Draw(mSystem.GUIMgr.GetButton(BUTTONS::MUTE_BUTTON_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::CLOSE_BUTTON_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::MINI_BUTTON_ID).GetSprite());
}

void RenderManager::PlayStateRender()
{
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::NEXT_LEVEL_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::OPEN_INVENTORY_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::EXIT_PLAY_ID).GetSprite());

	Draw(mSystem.GUIMgr.GetButton(BUTTONS::NEXT_LEVEL_ID).GetText());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::OPEN_INVENTORY_ID).GetText());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::EXIT_PLAY_ID).GetText());

	Draw(mSystem.GUIMgr.GetButton(BUTTONS::MUTE_BUTTON_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::UPGRADE_BUTTON_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::INFO_BUTTON_ID).GetSprite());

	Draw(mSystem.GUIMgr.GetButton(BUTTONS::CLOSE_BUTTON_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::MINI_BUTTON_ID).GetSprite());

	InventoryRender();
	ItemCollectionRender();
}

void RenderManager::WinStateRender()
{
	FireWorksRender();
	Draw(mSystem.AssetMgr.GetSprite(SPRITES::WINSCREEN));
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::NEW_GAME_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::NEW_GAME_ID).GetText());
	if (mSystem.TimeMgr.IsSpeedrun())
	{
		SpeedRunTimeRender();
	}
}

void RenderManager::InventoryRender()
{
	ItemsMissingListRender();

	if (!mSystem.InventoryMgr.IsOpen())
	{
		return;
	}

	Draw(mSystem.AssetMgr.GetSprite(SPRITES::INVENTORY));

	// Inventory buttons
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::INVENTORY_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::SORT_BUTTON_ID).GetSprite());

	// Render the amount of gold
	sf::Text goldText = mSystem.AssetMgr.GetTextForItemID(ITEMID::GOLD);
	goldText.setString(std::to_string(mSystem.InventoryMgr.GetGold()));
	goldText.setOrigin(-8.f, goldText.getLocalBounds().getSize().y + 2.f);
	goldText.setPosition({ 1365, 922 });
	mGameWindow.draw(goldText);

	auto& slots = mSystem.InventoryMgr.getItemSlots();
	auto& rects = mSystem.InventoryMgr.getSlotRects();

	int clickedDownIndex = mSystem.InventoryMgr.GetClickedDownIndex();

	for (int i{ 0 }; i < slots.size(); i++)
	{
		if (i == clickedDownIndex)
		{
			continue;
		}
		if (slots[i].IsEmpty())
		{
			continue;
		}
		sf::Color blue({ 82 , 075, 143 , 100 });
		sf::Color green({ 44 , 190, 52, 100 });

		rects[i].setFillColor(blue);

		if (mSystem.InventoryMgr.IsMouseOverSlot())
		{
			if (mSystem.InventoryMgr.GetMouseOverSlotIndex() == i)
			{
				rects[i].setFillColor(green);
			}
			else
			{
				rects[i].setFillColor(blue);
			}
		}

		mGameWindow.draw(rects[i]);

		sf::Sprite itemSprite = mSystem.AssetMgr.GetSpriteForItem(slots[i].GetItemId().first);
		itemSprite.setOrigin({ itemSprite.getLocalBounds().getSize().x / 2.f, itemSprite.getLocalBounds().getSize().y / 2.f });
		itemSprite.setPosition(rects[i].getPosition());

		mGameWindow.draw(itemSprite);
	}
	// If mouse is over a valid slot, render item name and text box
	if (mSystem.InventoryMgr.IsMouseOverSlot())
	{
		int index = mSystem.InventoryMgr.GetMouseOverSlotIndex();
		sf::Text hoverText = mSystem.AssetMgr.GetTextForItemID(slots[index].GetItemId().first);
		if (slots[index].GetQuantity() > 1)
		{
			hoverText.setString(hoverText.getString() + '\n' + "Quantity: " + std::to_string(slots[index].GetQuantity()));
		}
		hoverText.setOrigin(hoverText.getLocalBounds().getSize().x / 2, hoverText.getLocalBounds().getSize().y / 2);
		hoverText.setPosition(mSystem.InventoryMgr.GetLastMousePos().x, mSystem.InventoryMgr.GetLastMousePos().y - 20);
		hoverText.setColor(mSystem.AssetMgr.GetColorForItemText(slots[index].GetItemId()));
		// Text box to got under text
		sf::RectangleShape textBox{ sf::Vector2f{hoverText.getGlobalBounds().getSize().x + FONTS::PADDING, hoverText.getGlobalBounds().getSize().y + FONTS::PADDING} };
		textBox.setOrigin(textBox.getLocalBounds().getSize().x / 2 + FONTS::ORIGIN_YOFFSET, (textBox.getLocalBounds().getSize().y / 2) + FONTS::ORIGIN_YOFFSET);
		textBox.setFillColor(mSystem.AssetMgr.GetTextboxColor());
		textBox.setPosition(hoverText.getPosition());
		mGameWindow.draw(textBox);
		mGameWindow.draw(hoverText);
	}
	// Render the currently clicked item for swapping
	if (mSystem.InventoryMgr.IsItemSlotClicked())
	{
		ITEMID::ITEM clickedItem = mSystem.InventoryMgr.GetItemIdOfSlotClicked();
		sf::Sprite clickedSprite = mSystem.AssetMgr.GetSpriteForItem(clickedItem);
		clickedSprite.setOrigin(clickedSprite.getLocalBounds().getSize().x / 2.f, clickedSprite.getLocalBounds().getSize().y / 2.f);
		clickedSprite.setColor({ 255, 255, 255, 150 });
		clickedSprite.setPosition(mSystem.InventoryMgr.GetLastMousePos().x, mSystem.InventoryMgr.GetLastMousePos().y);
		Draw(clickedSprite);
	}
}

void RenderManager::SpeedRunTimeRender()
{
	int totalMilliseconds = mSystem.TimeMgr.GetSpeedRunTime();
	int hours = totalMilliseconds / (1000 * 60 * 60);
	totalMilliseconds %= (1000 * 60 * 60);
	int minutes = totalMilliseconds / (1000 * 60);
	totalMilliseconds %= (1000 * 60);
	int seconds = totalMilliseconds / 1000;
	int milliseconds = totalMilliseconds % 1000;
	std::stringstream timeStream;
	timeStream << "Completed in: \n " << std::setfill('0') << std::setw(2) << hours << ":"
		<< std::setw(2) << minutes << ":"
		<< std::setw(2) << seconds << "::"
		<< std::setw(3) << milliseconds << std::endl;
	std::string timeString = timeStream.str();
	sf::Text timeText;
	timeText.setFont(mSystem.AssetMgr.GetFont(FONTS::BOLD));
	timeText.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
	timeText.setString(timeString);
	timeText.setOrigin(timeText.getLocalBounds().getSize().x / 2, timeText.getLocalBounds().getSize().y / 2);
	timeText.setPosition(mWindowCenter - sf::Vector2f{0.f, 100.f});
	timeText.setOutlineThickness(1.f);
	timeText.setOutlineColor(sf::Color::Black);
	Draw(timeText);
}

sf::Sprite& RenderManager::AnimatedFire(ANIMATE::FIRE fireSize, const sf::Vector2f& position, const float scale)
{
	static sf::Sprite fireSprite = mSystem.AssetMgr.GetSprite(SPRITES::FIRE);

	int frameWidth = 0;
	int frameHeight = 0;
	int startX = 0;
	int startY = 0;
	const int frameSeparation = 2;
	int currentFrame = mSystem.TimeMgr.GetFireAnimFrame();

	switch (fireSize)
	{
	case ANIMATE::SMALL_FIRE:
		frameWidth = 46 - 1;
		frameHeight = 92 - 17;
		startX = 3 + currentFrame * (frameWidth + frameSeparation);
		startY = 19;
		break;

	case ANIMATE::MEDIUM_FIRE:
		frameWidth = 69 - 1;
		frameHeight = 210 - 110;
		startX = 1 + currentFrame * (frameWidth + frameSeparation);
		startY = 110;
		break;

	case ANIMATE::LARGE_FIRE:
		frameWidth = 118 - 1;
		frameHeight = 414 - 228;
		startX = 2 + currentFrame * (frameWidth + frameSeparation);
		startY = 228;
		break;
	}
	sf::IntRect frameRect(startX, startY, frameWidth, frameHeight);
	fireSprite.setTextureRect(frameRect);
	fireSprite.setOrigin(frameWidth / 2.0f, frameHeight);
	fireSprite.setPosition(position);
	fireSprite.setScale(sf::Vector2f{ scale, scale });

	return fireSprite;
}

void RenderManager::FireRenderer(LEVELS::LEVEL level)
{
	mSystem.TimeMgr.UpdateFireFrame();
	switch (level)
	{
	case LEVELS::LEVEL_ONE:
		Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 1108.f, 474.f }, 0.8f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 904.f, 163.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 360.f, 34.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 72.f, 306.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 519.f, 624.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 791.f, 904.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1431.f, 602.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1592.f, 298.f }, 0.5f));
		return;
	case LEVELS::LEVEL_TWO:
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 88.f, 58.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 138.f, 803.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 456.f, 642.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 408.f, 938.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 730.f, 778.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 905.f, 351.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1225.f, 515.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1481.f, 82.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1832.f, 259.f }, 0.5f));
		return;
	case LEVELS::LEVEL_THREE:
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 283.f, 665.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 679.f, 946.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1380.f, 256.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 925.f, 349.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1648.f, 70.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 196.f, 782.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 570.f, 590.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 844.f, 714.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1404.f, 976.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1149.f, 301.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1436.f, 434.f }, 0.5f));
		return;
	case LEVELS::LEVEL_FOUR:
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1442.f, 330.f }, 0.5f));
		return;
	case LEVELS::LEVEL_FIVE:
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 128.f, 152.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 95.f, 408.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 798.f, 264.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 976.f, 145.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 975.f, 305.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1216.f, 265.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1725.f, 174.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1873.f, 416.f }, 0.5f));
		return;
	case LEVELS::LEVEL_SIX:
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1369.f, 20.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1256.f, 28.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1049.f, 85.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 953.f, 132.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 808.f, 236.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 776.f, 299.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 761.f, 420.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 793.f, 500.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 888.f, 595.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1017.f, 660.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1240.f, 723.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1369.f, 740.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1608.f, 731.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1736.f, 716.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1593.f, 20.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1721.f, 37.f }, 1.f));
		return;
	case LEVELS::LEVEL_SEVEN:
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1415.f, 96.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 855.f, 327.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1111.f, 473.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 457.f, 335.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 710.f, 656.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1302.f, 681.f }, 0.5f));
		return;
	case LEVELS::LEVEL_EIGHT:
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 238.f, 232.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 494.f, 360.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 975.f, 584.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1358.f, 312.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1647.f, 137.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1311.f, 800.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1327.f, 887.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1455.f, 953.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1615.f, 936.f }, 0.5f));
		return;
	case LEVELS::LEVEL_NINE:
		return;
	case LEVELS::LEVEL_TEN:
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 88.f, 181.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 249.f, 101.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 409.f, 20.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 778.f, 524.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 808.f, 459.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 969.f, 381.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1112.f, 356.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1528.f, 309.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 504.f, 295.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 728.f, 181.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 1739.f, 888.f }, 1.f));
		return;
	case LEVELS::LEVEL_ELEVEN:
		Draw(AnimatedFire(ANIMATE::LARGE_FIRE, sf::Vector2f{ 1212.f, 712.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 1081.f, 360.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::MEDIUM_FIRE, sf::Vector2f{ 721.f, 659.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 696.f, 437.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1133.f, 367.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1269.f, 720.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1373.f, 489.f }, 1.f));
		return;
	case LEVELS::LEVEL_TWELVE:
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 903.f, 89.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1351.f, 327.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 728.f, 315.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 903.f, 227.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 823.f, 524.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 968.f, 437.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1143.f, 348.f }, 0.5f));
		return;
	case LEVELS::LEVEL_THIRTEEN:
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1216.f, 288.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1184.f, 386.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1344.f, 466.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1585.f, 456.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 96.f, 880.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 271.f, 793.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 176.f, 1001.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 337.f, 923.f }, 0.5f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 480.f, 334.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 337.f, 536.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 545.f, 638.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 705.f, 719.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 928.f, 832.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1311.f, 847.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1794.f, 606.f }, 1.f));
		Draw(AnimatedFire(ANIMATE::SMALL_FIRE, sf::Vector2f{ 1889.f, 958.f }, 1.f));
		return;
	default:
		return;
	}
}

sf::Sprite& RenderManager::GheedAnimation(const sf::Vector2f& position)
{
	static sf::Sprite gheedSprite = mSystem.AssetMgr.GetSprite(SPRITES::GHEED);  // Assuming you have a sprite for Gheed.
	gheedSprite.setScale(sf::Vector2f{ 1.4f,1.4f });
	// Idle frames
	const int frameWidth = 29 - 0;
	const int frameHeight = 556 - 488;
	// Walkingframes
	//const int frameWidth = 278 - 239;
	//const int frameHeight = 563 - 495;

	const int totalFrames = 8;

	// Get the current animation frame from TimeManager
	int currentFrame = mSystem.TimeMgr.GetGheedAnimFrame();  // You'll need to implement this similar to fire animation frame update.
	// Idle start
	int startX = currentFrame * frameWidth;
	int startY = 488;

	// Walking
	//int startX = 239 + (currentFrame * frameWidth);
	//int startY = 495;

	// Set texture rectangle for the current frame
	sf::IntRect frameRect(startX, startY, frameWidth, frameHeight);
	gheedSprite.setTextureRect(frameRect);

	// Set origin to the center for positioning
	gheedSprite.setOrigin(frameWidth / 2.0f, frameHeight);

	// Set the position and return the sprite
	gheedSprite.setPosition(position);

	return gheedSprite;
}

void RenderManager::RainRender()
{
	// Get raining timing
	mSystem.TimeMgr.UpdateRainProgress();
	auto& rainProgressBG = mSystem.TimeMgr.GetRainProgressBG();
	auto& rainProgressFG = mSystem.TimeMgr.GetRainProgressFG();

	//Get rain sprites
	sf::Sprite rainBG = mSystem.AssetMgr.GetSprite(SPRITES::RAIN_BG);
	sf::Sprite rainFG = mSystem.AssetMgr.GetSprite(SPRITES::RAIN_FG);
	//Get Window sizes for offsetting
	float windowX{ (float)GetWindow().getSize().x };
	float windowY{ (float)GetWindow().getSize().y };
	
	//Modulate rain color/opacity
	rainBG.setColor({ 255,255,255,80 });
	rainFG.setColor({ 255,255,255,60 });

	// Offset rain by rainprogress
	sf::Vector2f offsetBG{ -(windowX * rainProgressBG.first), windowY * rainProgressBG.second };
	sf::Vector2f offsetFG{ -(windowX * rainProgressFG.first), windowY * rainProgressFG.second };

	// Offset for each panel
	sf::Vector2f origin{ 0.f,0.f };
	sf::Vector2f topOffset{ 0.f, -windowY };
	sf::Vector2f rightOffset{ windowX, 0 };
	sf::Vector2f topRightOffset{ windowX, -windowY };
	
	//BACKGROUND RAIN
	//Draw rain center
	rainBG.move(offsetBG);
	Draw(rainBG);
	//Draw rain top
	rainBG.setPosition(origin);
	rainBG.move(offsetBG + topOffset);
	Draw(rainBG);
	//Draw rain right
	rainBG.setPosition(origin);
	rainBG.move(offsetBG + rightOffset);
	Draw(rainBG);
	//Draw rain top-right
	rainBG.setPosition(origin);
	rainBG.move(offsetBG + topRightOffset);
	Draw(rainBG);

	//FOREGROUND RAIN
	//Draw rain center
	rainFG.move(offsetFG);
	Draw(rainFG);
	//Draw rain top
	rainFG.setPosition(origin);
	rainFG.move(offsetFG + topOffset);
	Draw(rainFG);
	//Draw rain right
	rainFG.setPosition(origin);
	rainFG.move(offsetFG + rightOffset);
	Draw(rainFG);
	//Draw rain top-right
	rainFG.setPosition(origin);
	rainFG.move(offsetFG + topRightOffset);
	Draw(rainFG);
}

void RenderManager::ScreenFlash()
{
	sf::RectangleShape flash{ {(float)mGameWindow.getSize().x, (float)mGameWindow.getSize().y} };
	float thunderProgress = mSystem.TimeMgr.GetThunderProgress();
	if (thunderProgress > 0.5)
	{
		thunderProgress = 0.5f - (thunderProgress - 0.5f);
	}
	thunderProgress *= 2;
	flash.setFillColor({ 255, 255, 255, (sf::Uint8)(120 * thunderProgress)});
	Draw(flash);
}

void RenderManager::MerchantRender(Level& level)
{
	Merchant& merchant = level.GetMerchant();
	if (!merchant.IsVisible()) { return; }

	sf::Sprite gheed;
	if (merchant.IsWalking())
	{
		gheed = GetGheedWalkFrame(merchant);
	}
	else
	{
		gheed = GetGheedIdleFrame(merchant);
	}
	gheed.setPosition(merchant.GetCurrentPosition()); 
	Draw(gheed);

	if (merchant.IsDialogueOpen())
	{
		sf::Sprite purchase_btn = mSystem.AssetMgr.GetSprite(SPRITES::PURCHASE_BUTTON);
		sf::Vector2f btnPos = merchant.GetPurchaseButtonRect().getPosition();
		purchase_btn.setPosition(btnPos);
		Draw(purchase_btn);

		if (merchant.IsMouseOverPurchase())
		{
			//Get font
			sf::Font font = mSystem.AssetMgr.GetFont(FONTS::LIGHT);
			//Set Up Item Text
			std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item = merchant.GetItem();
			sf::Text itemText = mSystem.AssetMgr.GetTextForItemID(item.first);
			itemText.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
			itemText.setColor(mSystem.AssetMgr.GetColorForItemText(item));
			itemText.setString(itemText.getString() + " (" + mSystem.AssetMgr.GetRarityAsString(item.second) + ")");
			//Set Up Title Text
			std::string titlestr{ "You can buy a missing item: " };
			sf::Text titleText;
			titleText.setFont(font);
			titleText.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
			titleText.setString(titlestr);
			//Set Up Cost Text
			std::string coststr{ "For the price of: " };
			coststr += (std::to_string(merchant.CalculcateMissingItemCost()));
			coststr += (" Gold!");
			sf::Text costText;
			costText.setFont(font);
			costText.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
			costText.setString(coststr);

			titleText.setOrigin(titleText.getGlobalBounds().getSize().x / 2, titleText.getGlobalBounds().getSize().y / 2);
			itemText.setOrigin(itemText.getGlobalBounds().getSize().x / 2, itemText.getGlobalBounds().getSize().y / 2);
			costText.setOrigin(costText.getGlobalBounds().getSize().x / 2, costText.getGlobalBounds().getSize().y / 2);

			sf::Vector2f textPos{ btnPos + sf::Vector2f{ 0.f, 200.f } };
			titleText.setPosition(textPos);
			itemText.setPosition(textPos);
			itemText.move(0.f, titleText.getLocalBounds().getSize().y + FONTS::PADDING);
			costText.setPosition(itemText.getPosition());
			costText.move(0.f, itemText.getLocalBounds().getSize().y + FONTS::PADDING);

			Draw(titleText);
			Draw(itemText);
			Draw(costText);

			

		}
	}
}

sf::Sprite RenderManager::GetGheedIdleFrame(Merchant& merchant)
{
	sf::Sprite gheedSprite = mSystem.AssetMgr.GetSprite(SPRITES::GHEED); 
	gheedSprite.setScale(sf::Vector2f{ 1.4f,1.4f });
	// Idle frames
	const int frameWidth = 29 - 0;
	const int frameHeight = 556 - 488;

	// Get the current animation frame from TimeManager
	int currentFrame = merchant.GetIdleFrame();  // You'll need to implement this similar to fire animation frame update.
	// Idle start
	int startX = currentFrame * frameWidth;
	int startY = 488;

	// Set texture rectangle for the current frame
	sf::IntRect frameRect(startX, startY, frameWidth, frameHeight);
	gheedSprite.setTextureRect(frameRect);

	// Set origin to the center for positioning
	gheedSprite.setOrigin(frameWidth / 2.0f, frameHeight);

	return gheedSprite;
}

sf::Sprite RenderManager::GetGheedWalkFrame(Merchant& merchant)
{
	sf::Sprite gheedSprite = mSystem.AssetMgr.GetSprite(SPRITES::GHEED);
	gheedSprite.setScale(sf::Vector2f{ 1.4f,1.4f });
	// Walking frames
	const int frameWidth = 278 - 239;
	const int frameHeight = 563 - 495;

	// Get the current animation frame from TimeManager
	int currentFrame = merchant.GetWalkFrame();  // You'll need to implement this similar to fire animation frame update.
	// Walking
	int startX = 239 + (currentFrame * frameWidth);
	int startY = 495;
	std::cout << currentFrame << '\n';

	// Set texture rectangle for the current frame
	sf::IntRect frameRect(startX, startY, frameWidth, frameHeight);
	gheedSprite.setTextureRect(frameRect);

	// Set origin to the center for positioning
	gheedSprite.setOrigin(frameWidth / 2.0f, frameHeight);

	return gheedSprite;	
}




void RenderManager::LevelRender(Level& level)
{
	Draw(mSystem.AssetMgr.GetLevelMap(level.GetLevelId()));
	FireRenderer(level.GetLevelId());
	ChestsRender(level.GetChests());
	ParticlesRender(level.GetParticles());
	ItemsRender(level.GetItems());
	if (level.HasMerchant())
	{
		MerchantRender(level);
	}

	if (level.HasRain())
	{
		RainRender();
		if (level.ThunderStrike())
		{
			ScreenFlash();
		}
	}
}

void RenderManager::DrawToolTip(sf::Vector2f mousePos)
{
	if (mSystem.GUIMgr.GetButton(BUTTONS::MUTE_BUTTON_ID).GetSprite().getGlobalBounds().contains(mousePos))
	{
		sf::Text tooltipText;
		tooltipText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		tooltipText.setString("| Toggle Mute |\n\n1: SFX only\n2: Mute All\n3: Unmute");
		tooltipText.setCharacterSize(25);
		tooltipText.setFillColor(sf::Color::White);

		sf::FloatRect textBounds = tooltipText.getLocalBounds();
		float textWidth = textBounds.width;
		float textHeight = textBounds.height;

		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(textWidth + 20.f, textHeight + 20.f));
		backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));

		float xPos = mousePos.x - (backgroundRect.getSize().x / 2.f - 200.f);
		float yPos = mousePos.y - backgroundRect.getSize().y + 80.f;
		backgroundRect.setPosition(xPos, yPos);

		tooltipText.setPosition(xPos + 10.f, yPos + 5.f);

		mSystem.RenderMgr.Draw(backgroundRect);
		mSystem.RenderMgr.Draw(tooltipText);
	}
	if (mSystem.GUIMgr.GetButton(BUTTONS::UPGRADE_BUTTON_ID).GetSprite().getGlobalBounds().contains(mousePos))
	{
		sf::Text tooltipText;
		tooltipText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		LEVELS::UPGRADE currentUpgrade = mSystem.LevelMgr.GetCurrentLevel().GetUpgradeLevel();
		if ((int)currentUpgrade == (int)(LEVELS::MAX_UPGRADES - 1))
		{
			tooltipText.setString(" At Max Upgrade! \n");
		}
		else
		{
			std::string nextUpgrade = " | Upgrade Cost | \n\n    ";
			nextUpgrade += std::to_string(mSystem.AssetMgr.GetCostForNextLevelUpgrade(currentUpgrade));
			nextUpgrade += " Gold";
			tooltipText.setString(nextUpgrade);
		}

		tooltipText.setCharacterSize(25);
		tooltipText.setFillColor(sf::Color::White);

		sf::FloatRect textBounds = tooltipText.getLocalBounds();
		float textWidth = textBounds.width;
		float textHeight = textBounds.height;

		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(textWidth + 20.f, textHeight + 20.f));
		backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));

		float xPos = mousePos.x - (backgroundRect.getSize().x / 2.f - 215.f);
		float yPos = mousePos.y - backgroundRect.getSize().y + 80.f;
		backgroundRect.setPosition(xPos, yPos);

		tooltipText.setPosition(xPos + 10.f, yPos + 5.f);

		mSystem.RenderMgr.Draw(backgroundRect);
		mSystem.RenderMgr.Draw(tooltipText);
	}
	if (mSystem.GUIMgr.GetButton(BUTTONS::SORT_BUTTON_ID).GetSprite().getGlobalBounds().contains(mousePos) && mSystem.InventoryMgr.IsOpen())
	{
		sf::Text tooltipText;
		tooltipText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		tooltipText.setString("Auto Sort Inventory");
		tooltipText.setCharacterSize(25);
		tooltipText.setFillColor(sf::Color::White);

		sf::FloatRect textBounds = tooltipText.getLocalBounds();
		float textWidth = textBounds.width;
		float textHeight = textBounds.height;

		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(textWidth + 20.f, textHeight + 20.f));
		backgroundRect.setFillColor(sf::Color(0, 0, 0, 160));

		float xPos = mousePos.x - (backgroundRect.getSize().x / 2.f);
		float yPos = mousePos.y - backgroundRect.getSize().y - 10.f;
		backgroundRect.setPosition(xPos, yPos);

		tooltipText.setPosition(xPos + 10.f, yPos + 5.f);

		mSystem.RenderMgr.Draw(backgroundRect);
		mSystem.RenderMgr.Draw(tooltipText);
	}
	if (mSystem.GUIMgr.GetButton(BUTTONS::INFO_BUTTON_ID).GetSprite().getGlobalBounds().contains(mousePos))
	{
		sf::Text tooltipText;
		tooltipText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		tooltipText.setString("        | How to Play |\n\n   Collect all the items\nby clicking on the chests.\n  Click ~Next Level~ to\n            move on.\n    Collect Gold and to\n       upgrade levels.\n  Use the Upgrade to add\n      up to four chests.\n\n           | Hotkeys |\n          M: Mute all\n      I: Open Inventory\n       U: Upgrade Level\n         N: Next Level");
		tooltipText.setCharacterSize(25);
		tooltipText.setFillColor(sf::Color::White);

		sf::FloatRect textBounds = tooltipText.getLocalBounds();
		float textWidth = textBounds.width;
		float textHeight = textBounds.height;

		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(textWidth + 20.f, textHeight + 20.f));
		backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));

		float xPos = mousePos.x - (backgroundRect.getSize().x / 2.f - 280.f);
		float yPos = mousePos.y - backgroundRect.getSize().y + 280.f;
		backgroundRect.setPosition(xPos, yPos);

		tooltipText.setPosition(xPos + 10.f, yPos + 5.f);

		mSystem.RenderMgr.Draw(backgroundRect);
		mSystem.RenderMgr.Draw(tooltipText);
	}
}

void RenderManager::DrawToolTipWarning(sf::Vector2f mousePos)
{
	if (mSystem.GUIMgr.GetButton(BUTTONS::START_ID).GetSprite().getGlobalBounds().contains(mousePos))
	{
		sf::Text tooltipText;
		tooltipText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		tooltipText.setString("       WARNING!\nA New Game Erases\n  Your Progress.");
		tooltipText.setCharacterSize(25);
		tooltipText.setFillColor(sf::Color::White);

		sf::FloatRect textBounds = tooltipText.getLocalBounds();
		float textWidth = textBounds.width;
		float textHeight = textBounds.height;

		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(textWidth + 20.f, textHeight + 20.f));
		backgroundRect.setFillColor(sf::Color(0, 0, 0, 160));

		float xPos = mousePos.x - (backgroundRect.getSize().x / 2.f);
		float yPos = mousePos.y - backgroundRect.getSize().y - 10.f;
		backgroundRect.setPosition(xPos, yPos);

		tooltipText.setPosition(xPos + 10.f, yPos + 5.f);

		mSystem.RenderMgr.Draw(backgroundRect);
		mSystem.RenderMgr.Draw(tooltipText);
	}
	if (mSystem.GUIMgr.GetButton(BUTTONS::MUTE_BUTTON_ID).GetSprite().getGlobalBounds().contains(mousePos))
	{
		sf::Text tooltipText;
		tooltipText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		tooltipText.setString("| Toggle Mute |\n\n1: SFX only\n2: Mute All\n3: Unmute");
		tooltipText.setCharacterSize(25);
		tooltipText.setFillColor(sf::Color::White);

		sf::FloatRect textBounds = tooltipText.getLocalBounds();
		float textWidth = textBounds.width;
		float textHeight = textBounds.height;

		sf::RectangleShape backgroundRect;
		backgroundRect.setSize(sf::Vector2f(textWidth + 20.f, textHeight + 20.f));
		backgroundRect.setFillColor(sf::Color(0, 0, 0, 200));

		float xPos = mousePos.x - (backgroundRect.getSize().x / 2.f - 200.f);
		float yPos = mousePos.y - backgroundRect.getSize().y + 80.f;
		backgroundRect.setPosition(xPos, yPos);

		tooltipText.setPosition(xPos + 10.f, yPos + 5.f);

		mSystem.RenderMgr.Draw(backgroundRect);
		mSystem.RenderMgr.Draw(tooltipText);
	}
}

void RenderManager::ParticlesRender(std::list<std::unique_ptr<Particle>>& particles)
{
	for (auto& p : particles)
	{
		sf::Vector2f pos = p->GetCurrentPos();
		sf::Sprite particleSprite = mSystem.AssetMgr.GetSpriteForItem(p->GetItemID().first);
		particleSprite.setOrigin(particleSprite.getTextureRect().getSize().x / 2.f, particleSprite.getTextureRect().getSize().y / 2.f);
		particleSprite.setPosition(pos);
		float particleScale = p->GetProgress() * 0.5;
		particleSprite.setScale(particleScale, particleScale);
		Draw(particleSprite);
	}
}

void RenderManager::ChestsRender(std::array<std::unique_ptr<Chest>, 4>& chests)
{
	for (auto& chest : chests)
	{
		if (!chest->IsActive())
		{
			continue;
		}
		sf::Vector2f position = chest->GetPosition();
		sf::Sprite chestSprite;
		// Get the opened or closed sprite
		if (chest->IsOpened())
		{
			chestSprite = mSystem.AssetMgr.GetSprite(SPRITES::CHESTOPENED);
		}
		else
		{
			chestSprite = mSystem.AssetMgr.GetSprite(SPRITES::CHESTCLOSED);
		}
		chestSprite.setOrigin(chestSprite.getGlobalBounds().getSize().x / 2.f, chestSprite.getGlobalBounds().getSize().y / 2.f);
		chestSprite.setPosition(position);
		// Mirror it if needed
		if (chest->IsMirrored())
		{
			chestSprite.setScale({ -1,1 });
		}

		Draw(chestSprite);
	}
}

void RenderManager::ItemsRender(std::list<std::unique_ptr<Item>>& items)
{
	for (auto& item : items)
	{
		sf::Vector2f itemPos = item->GetPosition();
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item->GetItemID();
		sf::Sprite itemSprite;
		if (item->GetItemID().first == ITEMID::GOLD)
		{
			itemSprite = mSystem.AssetMgr.GetSpriteForGoldQuantity(item->GetQuantity());
		}
		else
		{
			itemSprite = mSystem.AssetMgr.GetSpriteForItem(itemId.first);
		}
		itemSprite.setScale(0.5, 0.5);
		itemSprite.setOrigin(itemSprite.getTextureRect().getSize().x / 2.f, itemSprite.getTextureRect().getSize().y / 2.f);
		itemSprite.setPosition(itemPos);


		mGameWindow.draw(itemSprite);
	}

	for (auto& item : items)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item->GetItemID();
		sf::RectangleShape textRect = item->GetTextRect();
		textRect.setFillColor(mSystem.AssetMgr.GetTextboxColor());
		sf::Text text = item->GetItemText();
		text.setOrigin(text.getGlobalBounds().getSize().x / 2, text.getGlobalBounds().getSize().y / 2);
		text.setPosition(textRect.getPosition());
		text.setColor(mSystem.AssetMgr.GetColorForItemText(itemId));
		mGameWindow.draw(textRect);
		mGameWindow.draw(text);
	}
}

void RenderManager::ItemCollectionRender()
{
	if (mSystem.InventoryMgr.IsOpen())
	{
		// Get the string with the appropriate numbers
		std::string string{ "Items Found: " };
		int uniqueItems = mSystem.InventoryMgr.GetNumberOfUniqueItems();
		if (uniqueItems < 100)
		{
			string += ' ';
		}
		if (uniqueItems < 10)
		{
			string += ' ';
		}
		string += std::to_string(uniqueItems);
		string += " / ";
		string += std::to_string(ITEMGEN::TOTAL_UNIQUE_ITEMS);

		// Create the SF::Text and TextRect
		sf::Text text;
		text.setString(string);
		text.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
		text.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
		text.setOrigin(text.getLocalBounds().getSize().x / 2.f, text.getLocalBounds().getSize().y / 2.f);

		//Set positions
		sf::Vector2f position{ 1483.f, 953.f };
		text.setPosition(position);

		//Draw
		Draw(text);
	}
}

void RenderManager::ItemsMissingListRender()
{
	if (!mSystem.InventoryMgr.IsItemListOn())
	{
		return;
	}

	auto& itemList = mSystem.InventoryMgr.GetItemFoundList();
	
	int count = 0;
	std::map<std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>, bool>::iterator it;
	sf::Vector2f initPos{ mWindowCenter - sf::Vector2f{0.f, 400.f} };
	std::vector<sf::Text> textVec;
	sf::Text title;
	title.setString("You are Missing:");
	title.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
	title.setColor(sf::Color::White);
	title.setOutlineColor(sf::Color::Black);
	title.setOutlineThickness(1);
	title.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
	title.setOrigin(title.getLocalBounds().getSize().x / 2, title.getLocalBounds().getSize().y / 2);
	title.setPosition(initPos);
	textVec.push_back(title);
	for (it = itemList.begin(); it != itemList.end(); it++)
	{
		if (count > 10)
		{
			break;
		}
		if(it->second == false)
		{
			count++;
			std::string itemMissing;
			itemMissing += (std::string)mSystem.AssetMgr.GetTextForItemID(it->first.first).getString();
			itemMissing += " (";
			itemMissing += mSystem.AssetMgr.GetRarityAsString(it->first.second);
			itemMissing += ")\n";
			
			sf::Text itemText;
			itemText.setString(itemMissing);
			itemText.setCharacterSize(FONTS::CHARACTER_SIZE_NORMAL);
			itemText.setColor(mSystem.AssetMgr.GetColorForItemText(it->first));
			itemText.setFont(mSystem.AssetMgr.GetFont(FONTS::LIGHT));
			sf::Vector2f pos = initPos + (sf::Vector2f{ 0.f, (itemText.getGlobalBounds().getSize().y * (float)count + 1) });
			itemText.setOrigin(itemText.getLocalBounds().getSize().x / 2, itemText.getLocalBounds().getSize().y / 2);
			itemText.setPosition(pos);
			textVec.push_back(itemText);
		}
	}
	float top = initPos.y;
	float bottom = initPos.y;
	float left = initPos.x;
	float right = initPos.x;
	for (auto& text : textVec)
	{
		if (text.getGlobalBounds().top < top)
		{
			top = text.getGlobalBounds().top;
		}
		if (text.getGlobalBounds().left < left)
		{
			left = text.getGlobalBounds().left;
		}
		if (text.getGlobalBounds().top + text.getGlobalBounds().height > bottom)
		{
			bottom = text.getGlobalBounds().top + text.getGlobalBounds().height;
		}
		if (text.getGlobalBounds().left + text.getGlobalBounds().width > right)
		{
			right = text.getGlobalBounds().left + text.getGlobalBounds().width;
		}
	}

	top -= 10.f;
	bottom += 10.f;
	left -= 10.f;
	right += 10.f;

	float width = right - left;
	float height = bottom - top;
	float centerx = right - (0.5 * width);
	float centery = bottom - (0.5 * height);
	sf::RectangleShape box;
	box.setSize({ width, height });
	box.setOrigin(box.getLocalBounds().getSize().x /2 , box.getLocalBounds().getSize().y / 2);
	box.setFillColor(mSystem.AssetMgr.GetTextboxColor());
	box.setPosition({ centerx, centery });
	Draw(box);

	for (auto& text : textVec)
	{
		Draw(text);
	}
}

void RenderManager::FireWorksRender()
{
	for (auto& fireWork : mSystem.FireWorks.GetFireWorks())
	{
		sf::Color color = fireWork->GetColor();
		sf::Vector2f pos = fireWork->GetCurrentPos();
		sf::Sprite particleSprite = mSystem.AssetMgr.GetSprite(SPRITES::PARTICLE);
		particleSprite.setOrigin(particleSprite.getTextureRect().getSize().x / 2.f, particleSprite.getTextureRect().getSize().y / 2.f);
		particleSprite.setPosition(pos);
		particleSprite.setColor(color);
		float particleScale = fireWork->GetProgress() * 0.5;
		particleSprite.setScale(particleScale, particleScale);
		particleSprite.setRotation(fireWork->GetProgress() * 3600);

		sf::Sprite glowSprite = mSystem.AssetMgr.GetSprite(SPRITES::GLOW);
		glowSprite.setOrigin(glowSprite.getTextureRect().getSize().x / 2.f, glowSprite.getTextureRect().getSize().y / 2.f);
		glowSprite.setPosition(particleSprite.getPosition());
		glowSprite.setColor({ color.r, color.g, color.b, 150 });
		glowSprite.setScale(particleSprite.getScale() * 1.5f);

		Draw(glowSprite);
		Draw(particleSprite);
	}
	for (auto& spark : mSystem.FireWorks.GetSparks())
	{
		sf::Color color = spark->GetColor();
		sf::Vector2f pos = spark->GetCurrentPos();
		sf::Sprite particleSprite = mSystem.AssetMgr.GetSprite(SPRITES::PARTICLE);
		particleSprite.setOrigin(particleSprite.getTextureRect().getSize().x / 2.f, particleSprite.getTextureRect().getSize().y / 2.f);
		particleSprite.setPosition(pos);
		particleSprite.setColor(color);
		float particleScale = 0.3  - (spark->GetProgress() * 0.3);
		particleSprite.setScale(particleScale, particleScale);
		particleSprite.setRotation(spark->GetProgress() * 3600);

		sf::Sprite glowSprite = mSystem.AssetMgr.GetSprite(SPRITES::GLOW);
		glowSprite.setOrigin(glowSprite.getTextureRect().getSize().x / 2.f, glowSprite.getTextureRect().getSize().y / 2.f);
		glowSprite.setPosition(particleSprite.getPosition());
		glowSprite.setColor({ color.r, color.g, color.b, 150 });
		glowSprite.setScale(particleSprite.getScale() * 1.5f);

		Draw(glowSprite);
		Draw(particleSprite);
	}
}
