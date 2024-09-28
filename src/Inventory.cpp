#include "Inventory.h"

Inventory::Inventory()
	:mGold{0}
	, mClickedDownIndex{-1}
	, mClickedReleaseIndex{-1}
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
	bool validSlot = false;
	for (int i{ 0 }; i < mSlotRects.size(); i++)
	{
		if (mSlotRects[i].getGlobalBounds().contains(mLastMousePos))
		{
			if (!mItemSlots[i].isEmpty())
			{
				mClickedDownIndex = i;
				validSlot = true;
			}
		}
	}
	if (!validSlot)
	{
		mClickedDownIndex = -1;
	}
}

void Inventory::OnMouseRelease(sf::Mouse::Button button)
{
	if (mClickedDownIndex == -1)
	{
		return;
	}
	bool validSlot = false;
	for (int i{ 0 }; i < mSlotRects.size(); i++)
	{
		if (mSlotRects[i].getGlobalBounds().contains(mLastMousePos) && (i != mClickedDownIndex))
		{
			//if (!mItemSlots[i].isEmpty())
			{
				mClickedReleaseIndex = i;
				validSlot = true;
			}
		}
	}
	if (!validSlot)
	{
		mClickedReleaseIndex = -1;
		mClickedDownIndex = -1;
	}
	else
	{
		swapSlots(mClickedReleaseIndex, mClickedDownIndex);
	}
}

void Inventory::swapSlots(int a, int b)
{
	std::swap(mItemSlots[a], mItemSlots[b]);
	mClickedDownIndex = -1;
	mClickedReleaseIndex = -1;
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
			else if (b.isEmpty())
			{
				return(a.getItemId().first < b.getItemId().first);
			}
			else if (a.getItemId().first == b.getItemId().first)
			{
				return(a.getItemId().second > b.getItemId().second);
			}
			else
			{
				return(a.getItemId().first > b.getItemId().first);
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
	if (item.getItemID().first == ITEMID::GOLD)
	{
		addGold(item.getQuantity());
		return true;
	}
	size_t index = getSlotForExistingItem(item);
	// If the item already exists in the inventory, add to it's quantity
	if (index != -1)
	{
		return false; 
		//mItemSlots[index].incrementQuantity(item.getQuantity());
		//return true;
	}
	// Otherwise, check if there is any slot available
	if (!availabeSlot())
	{
		return false;
	}
	// If there is, add it to that slot
	size_t emptySlot = getFirstOpenIndex();
	mItemSlots[emptySlot].setContainedItem(item.getItemID(), item.getQuantity());

	//sortInventory();

	return true;
}

void Inventory::addGold(int quantity)
{
	if (std::numeric_limits<int>::max() - quantity <= mGold)
	{
		mGold = std::numeric_limits<int>::max();
	}
	else
	{
		mGold += quantity;
	}
}

int Inventory::getGold()
{
	return mGold;
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

int Inventory::getClickedDownIndex()
{
	return mClickedDownIndex;
}

bool Inventory::isItemSlotClicked()
{
	return (mClickedDownIndex != -1);
}

ITEMID::ITEM Inventory::getItemIdOfSlotClicked()
{
	return mItemSlots[mClickedDownIndex].getItemId().first;
}

void Inventory::loadInventory()
{
	std::ifstream inData("inventoryData.inv");
	assert(inData && "InventoryManager::loadInventory failed to open inventoryData.inv file");
	std::string line;
	while (std::getline(inData, line))
	{
		if (line == "#GOLD")
		{
			std::getline(inData, line);
			std::cout << line << '\n';
			mGold = std::stoi(line);

		}
		if (line == "#SLOTS")
		{
			int index = 0;
			while (index < mItemSlots.size())
			{
				std::getline(inData, line);
				//std::cout << index << ": " << line << ' '; // debug
				int id = std::stoi(line);
				std::getline(inData, line);
				// std::cout << line << ' '; // debug
				int rarity = std::stoi(line);
				std::getline(inData, line);
				// std::cout << line << '\n'; // debug
				int quantity = std::stoi(line);
				mItemSlots[index] = ItemSlot{ id, rarity, quantity };
				index++;
			}
			break;
		}
	}
}

void Inventory::saveInventory()
{
	std::ofstream outData;
	outData.open("inventoryData.inv");
	assert(outData && "InventoryManager::saveInventory failed to open inventoryData.inv file");
	int gold = mGold;
	outData << "#GOLD\n" << gold << '\n';
	outData << "#SLOTS\n";
	for (int i{ 0 }; i < mItemSlots.size(); i++)
	{
		outData << mItemSlots[i].getItemId().first << '\n' << mItemSlots[i].getItemId().second << '\n' << mItemSlots[i].getQuantity() << '\n';
	}
	outData.close();
}

void Inventory::deleteInventory()
{
	for (auto& slot : mItemSlots)
	{
		slot = ItemSlot();
	}
}

bool Inventory::hasOneOfEverything()
{
	int uniqueItems = 0;
	for (auto& slot : mItemSlots)
	{
		if (!slot.isEmpty())
		{
			uniqueItems++;
		}
	}
	return uniqueItems == ITEMGEN::TOTAL_UNIQUE_ITEMS;
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