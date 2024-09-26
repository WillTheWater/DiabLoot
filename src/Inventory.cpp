#include "Inventory.h"

Inventory::Inventory()
{
	initialzeSlotRects();
}

void Inventory::OnMouseMove(int x, int y)
{
	mLastMousePos = sf::Vector2f{(float)x, (float)y };
	mMouseOver = false;
	for (int i{ 0 }; i < mSlotRects.size(); i++)
	{
		if (mSlotRects[i].getGlobalBounds().contains(mLastMousePos))
		{
			if(!mItemSlots[i].isEmpty())
			mMouseOver = true;
			mMouseOverSlotIndex = i;
		}
	}
}

void Inventory::OnKeyPress(sf::Keyboard::Key key)
{
}

void Inventory::OnKeyRelease(sf::Keyboard::Key key)
{
}

void Inventory::OnMouseClick(sf::Mouse::Button button)
{
}

void Inventory::OnMouseRelease(sf::Mouse::Button button)
{
}

void Inventory::ToggleInventory()
{
	mVisible = !mVisible;
}

bool Inventory::isOpen()
{
	return mVisible;
}

std::array<ItemSlot, 150>& Inventory::getItemSlots()
{
	return mItemSlots;
}

std::array<sf::RectangleShape, 150>& Inventory::getSlotRects()
{
	return mSlotRects;
}

bool Inventory::isMouseOverSlot()
{
	return mMouseOver;
}

int Inventory::getMouseOverSlotIndex()
{
	return mMouseOverSlotIndex;
}

sf::Vector2f Inventory::getLastMousePos()
{
	return mLastMousePos;
}

void Inventory::sortInventory()
{
	auto sortLamda = [](ItemSlot& a, ItemSlot& b)
		{
			if (a.isEmpty())
			{
				return false;
			}
			else if (a.getItemId().first == b.getItemId().first)
			{
				return(a.getItemId().second < b.getItemId().second);
			}
			else
			{
				return(a.getItemId().first < b.getItemId().first);
			}
		};

	std::sort(mItemSlots.begin(), mItemSlots.end(), sortLamda);
}

bool Inventory::doesItemAlreadyHaveASlot(Item& item)
{
	bool alreadyExists = false;
	for (auto& slot : mItemSlots)
	{
		if (slot.isEmpty())
		{
			continue;
		}
		if (slot.getItemId().first != item.getItemID().first)
		{
			continue;
		}
		if (slot.getItemId().second == item.getItemID().second)
		{
			alreadyExists = true;
			break;
		}
	}
	return alreadyExists;
}

size_t Inventory::getSlotForExistingItem(Item& item)
{
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item.getItemID();
	size_t index = -1;
	for (int i{ 0 }; i < mItemSlots.size(); i++)
	{
		if (mItemSlots[i].isEmpty())
		{
			continue;
		}
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> slotId = mItemSlots[i].getItemId();
		if (itemId.first == slotId.first && itemId.second == slotId.second)
		{
			index = (size_t)i;
			return index;
		}
	}
	return index;
}

bool Inventory::addItem(Item& item)
{
	size_t index = getSlotForExistingItem(item);
	// If the item already exists in the inventory, add to it's quantity
	if (index != -1)
	{
		mItemSlots[index].incrementQuantity(item.getQuantity());
		return true;
	}
	// Otherwise, check if there is any slot available
	if (!availabeSlot())
	{
		return false;
	}
	// If there is, add it to that slot
	size_t emptySlot = getFirstOpenIndex();
	mItemSlots[emptySlot].setContainedItem(item.getItemID(), item.getQuantity());

	sortInventory();

	return true;
}

bool Inventory::availabeSlot()
{
	bool available = false;
	for (auto& slot : mItemSlots)
	{
		if (slot.isEmpty())
		{
			available = true;
			return available;
		}
	}
	return available;
}

size_t Inventory::getFirstOpenIndex()
{
	int index = -1;
	for (int i{ 0 }; i < mItemSlots.size(); i++)
	{
		if (mItemSlots[i].isEmpty())
		{
			index = (size_t)i;
			return index;
		}
	}
	return index;
}

void Inventory::initialzeSlotRects()
{
	// Needs testing
	sf::RectangleShape slotTemplate{ {52.f, 52.f} };
	slotTemplate.setOrigin(slotTemplate.getSize().x / 2, slotTemplate.getSize().y / 2);
	slotTemplate.setPosition({ 1248.f, 145.f }); // Position for the top left slot
	for (int i{ 0 }; i < 150; i++)
	{
		
		mSlotRects[(int)i] = slotTemplate;
		mSlotRects[(int)i].move(i % 10 * 52, i / 10 * 52);
		
	}
}