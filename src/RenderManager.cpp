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

void RenderManager::LevelRender(Level& level)
{
	Draw(mSystem.AssetMgr.GetLevelMap(level.GetLevelId()));
	ChestsRender(level.GetChests());
	ParticlesRender(level.GetParticles());
	ItemsRender(level.GetItems());
}

void RenderManager::DrawToolTip(sf::Vector2f mousePos)
{
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
}

void RenderManager::ParticlesRender(std::vector<std::unique_ptr<Particle>>& particles)
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

void RenderManager::ChestsRender(std::vector<std::unique_ptr<Chest>>& chests)
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

void RenderManager::ItemsRender(std::vector<std::unique_ptr<Item>>& items)
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

		sf::Sprite glowSprite = mSystem.AssetMgr.GetSprite(SPRITES::GLOW);
		glowSprite.setOrigin(glowSprite.getTextureRect().getSize().x / 2.f, glowSprite.getTextureRect().getSize().y / 2.f);
		glowSprite.setPosition(particleSprite.getPosition());
		glowSprite.setColor({ color.r, color.g, color.b, 150 });
		glowSprite.setScale(particleSprite.getScale() * 1.5f);

		Draw(glowSprite);
		Draw(particleSprite);
	}
}
