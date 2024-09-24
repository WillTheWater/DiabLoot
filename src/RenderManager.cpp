#include "RenderManager.h"
#include "Core.h"

RenderManager::RenderManager(GUIManager& guiMgr)
	: mAssetMgr{}
	, mGameWindow{ sf::VideoMode(1920u, 1080u), "DiabLoot", sf::Style::Close }
	, mGUIMgr{guiMgr}
{
}

sf::RenderWindow& RenderManager::GetWindow()
{
	return mGameWindow;
}

void RenderManager::MainMenuRender()
{
	Draw(mAssetMgr.GetSprite(SPRITES::MAINMENU));
	DrawButtons();
}

void RenderManager::DrawButtons()
{
	auto mousePos = sf::Mouse::getPosition(mGameWindow);

	bool isLeftButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);

	for (const auto& button : mGUIMgr.GetButtons())
	{
		auto& buttonSprite = mAssetMgr.GetSprite(SPRITES::BUTTON);
		buttonSprite.setPosition(button->GetPosition());

		switch (button->GetButtonState())
		{
		case Button::BUTTON_STATE::HOVER:
			buttonSprite.setColor(sf::Color{ 200, 200, 200, 255 });
			break;
		case Button::BUTTON_STATE::CLICK:
			buttonSprite.setColor(sf::Color{ 100, 100, 100, 255 });
			break;
		default:
			buttonSprite.setColor(sf::Color{ 255, 255, 255, 255 });
			break;
		}

		Draw(buttonSprite);
	}
}


void RenderManager::RenderLevel(Level& level)
{
	Draw(mAssetMgr.GetLevelMap(level.GetLevelId()));
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
		sf::Sprite particleSprite = mAssetMgr.GetSpriteForItem(p->getItemID().first);
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
			chestSprite = mAssetMgr.GetSprite(SPRITES::CHESTOPENED);
		}
		else
		{
			chestSprite = mAssetMgr.GetSprite(SPRITES::CHESTCLOSED);
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
		sf::Sprite itemSprite = mAssetMgr.GetSpriteForItem(itemId.first);
		itemSprite.setScale(0.5, 0.5);
		itemSprite.setOrigin(itemSprite.getTextureRect().getSize().x / 2.f, itemSprite.getTextureRect().getSize().y / 2.f);
		itemSprite.setPosition(itemPos);
	

		mGameWindow.draw(itemSprite);
	}

	for (auto& item : items)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item->getItemID();
		sf::RectangleShape textRect = item->getTextRect();
		textRect.setFillColor(sf::Color{ 0,0,0,200 });
		sf::Text text = mAssetMgr.GetTextForItemID(itemId.first);
		text.setOrigin(text.getGlobalBounds().getSize().x / 2, text.getGlobalBounds().getSize().y / 2);
		text.setPosition(textRect.getPosition());
		switch (itemId.second)
		{
		case ITEMRARITY::NORMAL:	text.setColor(sf::Color::White);			break;
		case ITEMRARITY::MAGIC:		text.setColor(sf::Color{ 82, 075, 143 });	break;
		case ITEMRARITY::RARE:		text.setColor(sf::Color{ 253, 216, 53 });	break;
		case ITEMRARITY::SET:		text.setColor(sf::Color{ 44, 190, 52 });	break;
		case ITEMRARITY::UNIQUE:	text.setColor(sf::Color{ 153, 102, 51 });	break;
		case ITEMRARITY::RUNE:		text.setColor(sf::Color{ 198, 140, 89 });	break;
		default	:					text.setColor(sf::Color::White);			break;
		}
		mGameWindow.draw(textRect);
		mGameWindow.draw(text);
	}
}

sf::Text& RenderManager::GetTextForItemId(ITEMID::ITEM item)
{
	return mAssetMgr.GetTextForItemID(item);
}

void RenderManager::RenderInventory(Inventory& inventory)
{
	auto& slots = inventory.getItemSlots();
	auto& rects = inventory.getSlotRects();

	for (int i{ 0 }; i < slots.size(); i++)
	{
		if (slots[i].isEmpty())
		{
			continue;
		}

		sf::Sprite itemSprite = mAssetMgr.GetSpriteForItem(slots[i].getItemId().first);
		itemSprite.setOrigin({ itemSprite.getLocalBounds().getSize().x / 2.f, itemSprite.getLocalBounds().getSize().y / 2.f });
		itemSprite.setPosition(rects[i].getPosition());

		mGameWindow.draw(itemSprite);
	}

	if (inventory.isMouseOverSlot())
	{
		int index = inventory.getMouseOverSlotIndex();
		sf::Text hoverText = mAssetMgr.GetTextForItemID(slots[index].getItemId().first);
		hoverText.setString(hoverText.getString() + std::to_string(slots[index].getQuantity()));
		hoverText.setOrigin(0.f, -hoverText.getLocalBounds().getSize().y);
		hoverText.setPosition(inventory.getLastMousePos());
		mGameWindow.draw(hoverText);
	}

}