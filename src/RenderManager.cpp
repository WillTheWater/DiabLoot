#include "RenderManager.h"
#include "SystemManager.h"
#include "Core.h"

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

void RenderManager::InventoryRender()
{

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
	float dT = mSystem.TimeMgr.GetDeltaTime();
	static sf::Sprite fireSprite = mSystem.AssetMgr.GetSprite(SPRITES::FIRE);
	auto& fireTexture = mSystem.AssetMgr.GetTexture(TEXTURES::FIRE);

	// Create an sf::Image from the texture to apply the color mask
	sf::Image fireImage = fireTexture.copyToImage();
	fireImage.createMaskFromColor(sf::Color(255, 0, 153));
	fireTexture.loadFromImage(fireImage);

	// Variables to store the position and size of the frame
	int frameWidth, frameHeight, startX, startY;

	// Define frame separation (2 pixel between frames)
	const int frameSeparation = 2;

	static float frameTimer = 0.0f;
	const float frameDuration = .3f; // Adjust to control animation speed
	static int currentFrame = 0;  // Keeps track of the current frame
	const int maxFrames = 20;     // 20 frames per fire

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

	frameTimer += dT;
	if (frameTimer >= frameDuration)
	{
		currentFrame = (currentFrame + 1) % maxFrames;
		frameTimer = 0.0f;
	}
	return fireSprite;
}

void RenderManager::FireRenderer(LEVELS::LEVEL level)
{
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
	case LEVELS::LEVEL_THREE:
	case LEVELS::LEVEL_FOUR:
	case LEVELS::LEVEL_FIVE:
	case LEVELS::LEVEL_SIX:
	case LEVELS::LEVEL_SEVEN:
	case LEVELS::LEVEL_EIGHT:
	case LEVELS::LEVEL_NINE:
	case LEVELS::LEVEL_TEN:
	case LEVELS::LEVEL_ELEVEN:
	case LEVELS::LEVEL_TWELVE:
	case LEVELS::LEVEL_THIRTEEN:
	default:
		break;
	}
}




void RenderManager::LevelRender(Level& level)
{
	Draw(mSystem.AssetMgr.GetLevelMap(level.GetLevelId()));
	FireRenderer(level.GetLevelId());
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

void RenderManager::FireWorksRender(const FireWorkSystem& fireWorkSys)
{
	for (auto& fireWork : fireWorkSys.GetFireWorks())
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
	for (auto& spark : fireWorkSys.GetSparks())
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
