#include "Inventory.h"

Inventory::Inventory()
	:mGold{0}
	, mClickedDownIndex{-1}
	, mClickedReleaseIndex{-1}
{
	InitialzeSlotRects();
}

void Inventory::OnMouseMove(int x, int y)
{
	mLastMousePos = sf::Vector2f{(float)x, (float)y };
	mMouseOver = false;
	if (!mVisible) { return; }
	for (int i{ 0 }; i < mSlotRects.size(); i++)
	{
		if (mSlotRects[i].getGlobalBounds().contains(mLastMousePos))
		{
			if(!mItemSlots[i].IsEmpty())
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
	if (!mVisible) { return; }
	bool validSlot = false;
	
	for (int i{ 0 }; i < mSlotRects.size(); i++)
	{
		if (mSlotRects[i].getGlobalBounds().contains(mLastMousePos))
		{
			if (!mItemSlots[i].IsEmpty())
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
	if (!mVisible) { return; }
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
		SwapSlots(mClickedReleaseIndex, mClickedDownIndex);
	}
}

void Inventory::SwapSlots(int a, int b)
{
	std::swap(mItemSlots[a], mItemSlots[b]);
	mClickedDownIndex = -1;
	mClickedReleaseIndex = -1;
}

void Inventory::ToggleInventory()
{
	mVisible = !mVisible;
}

bool Inventory::IsOpen() const
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

bool Inventory::IsMouseOverSlot() const
{
	return mMouseOver;
}

int Inventory::GetMouseOverSlotIndex() const
{
	return mMouseOverSlotIndex;
}

sf::Vector2f Inventory::GetLastMousePos() const
{
	return mLastMousePos;
}

void Inventory::SortInventory()
{
	auto sortLamda = [](ItemSlot& a, ItemSlot& b)
		{
			if (a.IsEmpty())
			{
				return false;
			}
			else if (b.IsEmpty())
			{
				return(a.GetItemId().first < b.GetItemId().first);
			}
			else if (a.GetItemId().first == b.GetItemId().first)
			{
				return(a.GetItemId().second > b.GetItemId().second);
			}
			else
			{
				return(a.GetItemId().first > b.GetItemId().first);
			}
		};

	std::sort(mItemSlots.begin(), mItemSlots.end(), sortLamda);
}

bool Inventory::DoesItemAlreadyHaveASlot(Item& item)
{
	bool alreadyExists = false;
	for (auto& slot : mItemSlots)
	{
		if (slot.IsEmpty())
		{
			continue;
		}
		if (slot.GetItemId().first != item.GetItemID().first)
		{
			continue;
		}
		if (slot.GetItemId().second == item.GetItemID().second)
		{
			alreadyExists = true;
			break;
		}
	}
	return alreadyExists;
}

size_t Inventory::GetSlotForExistingItem(Item& item)
{
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> itemId = item.GetItemID();
	size_t index = -1;
	for (int i{ 0 }; i < mItemSlots.size(); i++)
	{
		if (mItemSlots[i].IsEmpty())
		{
			continue;
		}
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> slotId = mItemSlots[i].GetItemId();
		if (itemId.first == slotId.first && itemId.second == slotId.second)
		{
			index = (size_t)i;
			return index;
		}
	}
	return index;
}

bool Inventory::AddItem(Item& item)
{
	if (item.GetItemID().first == ITEMID::GOLD)
	{
		AddGold(item.GetQuantity());
		return true;
	}
	size_t index = GetSlotForExistingItem(item);
	// If the item already exists in the inventory, add to it's quantity
	if (index != -1)
	{
		return false; 
		//mItemSlots[index].incrementQuantity(item.getQuantity());
		//return true;
	}
	// Otherwise, check if there is any slot available
	if (!AvailabeSlot())
	{
		return false;
	}
	// If there is, add it to that slot
	size_t emptySlot = GetFirstOpenIndex();
	mItemSlots[emptySlot].SetContainedItem(item.GetItemID(), item.GetQuantity());

	//sortInventory();

	return true;
}

void Inventory::AddGold(int quantity)
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

void Inventory::RemoveGold(int quantity)
{
	if ((mGold - quantity) < 0)
	{
		mGold = 0;
	}
	else
	{
		mGold -= quantity;
	}
}

int Inventory::GetGold()
{
	return mGold;
}

bool Inventory::AvailabeSlot()
{
	bool available = false;
	for (auto& slot : mItemSlots)
	{
		if (slot.IsEmpty())
		{
			available = true;
			return available;
		}
	}
	return available;
}

size_t Inventory::GetFirstOpenIndex()
{
	int index = -1;
	for (int i{ 0 }; i < mItemSlots.size(); i++)
	{
		if (mItemSlots[i].IsEmpty())
		{
			index = (size_t)i;
			return index;
		}
	}
	return index;
}

int Inventory::GetClickedDownIndex() const
{
	return mClickedDownIndex;
}

bool Inventory::IsItemSlotClicked() const
{
	return (mClickedDownIndex != -1);
}

ITEMID::ITEM Inventory::GetItemIdOfSlotClicked()
{
	return mItemSlots[mClickedDownIndex].GetItemId().first;
}

void Inventory::LoadInventory()
{
	std::ifstream inData("save/inventoryData.inv");
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
				int id = std::stoi(line);
				std::getline(inData, line);
				int rarity = std::stoi(line);
				std::getline(inData, line);
				int quantity = std::stoi(line);
				mItemSlots[index] = ItemSlot{ id, rarity, quantity };
				index++;
			}
			break;
		}
	}
}

void Inventory::SaveInventory()
{
	std::ofstream outData;
	// Save the file in the inventory directory created by CMake
	std::string filePath = "save/inventoryData.inv"; // Relative path
	outData.open(filePath);
	assert(outData && "InventoryManager::saveInventory failed to open inventoryData.inv file");

	int gold = mGold;
	outData << "#GOLD\n" << gold << '\n';
	outData << "#SLOTS\n";
	for (int i{ 0 }; i < mItemSlots.size(); i++)
	{
		outData << mItemSlots[i].GetItemId().first << '\n'
			<< mItemSlots[i].GetItemId().second << '\n'
			<< mItemSlots[i].GetQuantity() << '\n';
	}
	outData.close();
}

void Inventory::DeleteInventory()
{
	for (auto& slot : mItemSlots)
	{
		slot = ItemSlot();
	}
}

int Inventory::GetNumberOfUniqueItems()
{
	int uniqueItems = 0;
	for (auto& slot : mItemSlots)
	{
		if (!slot.IsEmpty())
		{
			uniqueItems++;
		}
	}
	return uniqueItems;
}

bool Inventory::HasOneOfEverything()
{
	return GetNumberOfUniqueItems() == ITEMGEN::TOTAL_UNIQUE_ITEMS;
}

void Inventory::DebugGetOneOfEverything()
{
	for(int i{0}; i < ITEMGEN::RarityNormalItems.size(); i++)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> id = { ITEMGEN::RarityNormalItems[i], ITEMRARITY::NORMAL };
		Item item{ id, 1 };
		AddItem(item);
	}
	for (int i{ 0 }; i < ITEMGEN::RarityMagicItems.size(); i++)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> id = { ITEMGEN::RarityMagicItems[i], ITEMRARITY::MAGIC };
		Item item{ id, 1 };
		AddItem(item);
	}
	for (int i{ 0 }; i < ITEMGEN::RarityRareItems.size(); i++)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> id = { ITEMGEN::RarityRareItems[i], ITEMRARITY::RARE };
		Item item{ id, 1 };
		AddItem(item);
	}
	for (int i{ 0 }; i < ITEMGEN::RaritySetItems.size(); i++)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> id = { ITEMGEN::RaritySetItems[i], ITEMRARITY::SET };
		Item item{ id, 1 };
		AddItem(item);
	}
	for (int i{ 0 }; i < ITEMGEN::RarityUniqueItems.size(); i++)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> id = { ITEMGEN::RarityUniqueItems[i], ITEMRARITY::UNIQUE };
		Item item{ id, 1 };
		AddItem(item);
	}
	for (int i{ 0 }; i < ITEMGEN::RarityRuneItems.size(); i++)
	{
		std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> id = { ITEMGEN::RarityRuneItems[i], ITEMRARITY::RUNE };
		Item item{ id, 1 };
		AddItem(item);
	}
}

void Inventory::InitialzeSlotRects()
{
	sf::RectangleShape slotTemplate{ {52.f, 52.f} };
	slotTemplate.setOrigin(slotTemplate.getSize().x / 2, slotTemplate.getSize().y / 2);
	slotTemplate.setPosition({ 1248.f, 145.f }); // Position for the top left slot
	for (int i{ 0 }; i < 150; i++)
	{
		mSlotRects[(int)i] = slotTemplate;
		mSlotRects[(int)i].move(i % 10 * 52, (float)(i / 10 * 52));
	}
}