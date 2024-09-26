#include "RenderManager.h"
#include "SystemManager.h"
#include "Core.h"

RenderManager::RenderManager(System& system)
	: mGameWindow{ sf::VideoMode(1920u, 1080u), "DiabLoot", sf::Style::Close }
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
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::EXIT_ID).GetSprite());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::START_ID).GetText());
	Draw(mSystem.GUIMgr.GetButton(BUTTONS::EXIT_ID).GetText());
}

void RenderManager::PlayStateRender()
{
	auto nextLevelButton = mSystem.GUIMgr.MakeButton(BUTTONS::WIDE, BUTTONS::NEXT_LEVEL, mWindowCenter + sf::Vector2f{ 0.f, 500.f });
	Draw(nextLevelButton->GetSprite());
	Draw(nextLevelButton->GetText());
	InventoryRender();
}

void RenderManager::InventoryRender()
{
	
	if (!mSystem.InventoryMgr.isOpen())
	{
		return;
	}

	Draw(mSystem.AssetMgr.GetSprite(SPRITES::INVENTORY));
	// Inventory button
	auto inventoryButton = mSystem.GUIMgr.MakeInventoryButton(BUTTONS::SQUARE, { 1263.f, 940.f });
	Draw(inventoryButton->GetSprite());

	auto& slots = mSystem.InventoryMgr.getItemSlots();
	auto& rects = mSystem.InventoryMgr.getSlotRects();

	for (int i{ 0 }; i < slots.size(); i++)
	{
		//For Debug Purposes
		/*rects[i].setFillColor(sf::Color::Magenta);
		mGameWindow.draw(rects[i]);*/

		//End debug
		if (slots[i].isEmpty())
		{
			continue;
		}

		sf::Sprite itemSprite = mSystem.AssetMgr.GetSpriteForItem(slots[i].getItemId().first);
		itemSprite.setOrigin({ itemSprite.getLocalBounds().getSize().x / 2.f, itemSprite.getLocalBounds().getSize().y / 2.f });
		itemSprite.setPosition(rects[i].getPosition());

		mGameWindow.draw(itemSprite);
	}
	// If mouse is over a valid slot, render item name and text box
	if (mSystem.InventoryMgr.isMouseOverSlot())
	{
		int index = mSystem.InventoryMgr.getMouseOverSlotIndex();
		sf::Text hoverText = mSystem.AssetMgr.GetTextForItemID(slots[index].getItemId().first);
		if (slots[index].getQuantity() > 1)
		{
			hoverText.setString(hoverText.getString() + " x " + std::to_string(slots[index].getQuantity()));
		}
		hoverText.setOrigin(0.f, -hoverText.getLocalBounds().getSize().y);
		hoverText.setPosition(mSystem.InventoryMgr.getLastMousePos());
		hoverText.setColor(mSystem.AssetMgr.GetColorForRarity(slots[index].getItemId().second));
		// Text box to got under text
		sf::RectangleShape textBox{ sf::Vector2f{hoverText.getGlobalBounds().getSize().x + FONTS::PADDING, hoverText.getGlobalBounds().getSize().y + FONTS::PADDING} };
		textBox.setOrigin(0, -textBox.getLocalBounds().getSize().y - FONTS::ORIGIN_YOFFSET);
		textBox.setFillColor(mSystem.AssetMgr.GetTextboxColor());
		textBox.setPosition(hoverText.getPosition());
		mGameWindow.draw(textBox);
		mGameWindow.draw(hoverText);
	}
}


void RenderManager::RenderLevel(Level& level)
{
	Draw(mSystem.AssetMgr.GetLevelMap(level.GetLevelId()));
	RenderChests(level.GetChests());
	RenderParticles(level.GetParticles());
	RenderItems(level.GetItems());
}

void RenderManager::RenderParticles(std::vector<std::unique_ptr<Particle>>& particles)
{
	for (auto& p : particles)
	{
		sf::Vector2f pos = p->getCurrentPos();
		// Change this to the correct sprite
		sf::Sprite particleSprite = mSystem.AssetMgr.GetSpriteForItem(p->getItemID().first);
		particleSprite.setOrigin(particleSprite.getTextureRect().getSize().x / 2.f, particleSprite.getTextureRect().getSize().y / 2.f);
		particleSprite.setPosition(pos);
		float particleScale = p->getProgress() * 0.5;
		particleSprite.setScale(particleScale, particleScale);
		Draw(particleSprite);
	}
}

void RenderManager::RenderChests(std::vector<std::unique_ptr<Chest>>& chests)
{
	for (auto& chest : chests)
	{
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

void RenderManager::RenderItems(std::vector<std::unique_ptr<Item>>& items)
{
	for (auto& item : items)
	{
		sf::Vector2f itemPos = item->getPosition();
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item->getItemID();
		sf::Sprite itemSprite = mSystem.AssetMgr.GetSpriteForItem(itemId.first);
		itemSprite.setScale(0.5, 0.5);
		itemSprite.setOrigin(itemSprite.getTextureRect().getSize().x / 2.f, itemSprite.getTextureRect().getSize().y / 2.f);
		itemSprite.setPosition(itemPos);


		mGameWindow.draw(itemSprite);
	}

	for (auto& item : items)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item->getItemID();
		sf::RectangleShape textRect = item->getTextRect();
		textRect.setFillColor(mSystem.AssetMgr.GetTextboxColor());
		sf::Text text = mSystem.AssetMgr.GetTextForItemID(itemId.first);
		text.setOrigin(text.getGlobalBounds().getSize().x / 2, text.getGlobalBounds().getSize().y / 2);
		text.setPosition(textRect.getPosition());
		text.setColor(mSystem.AssetMgr.GetColorForRarity(itemId.second));
		mGameWindow.draw(textRect);
		mGameWindow.draw(text);
	}
}