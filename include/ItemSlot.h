#pragma once
#include "Assets.h"
#include <utility>

class ItemSlot
{
public:
	ItemSlot();
	ItemSlot(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity);
	ItemSlot(int id, int rartity, int quantity);

	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> GetItemId();

	bool operator== (const ItemSlot& other);

	bool										IsEmpty();
	int											GetQuantity();
	void										IncrementQuantity(int amount = 1);
	void										SetContainedItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity = 1);
	void										ToggleEmpty(bool empty);

private:
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> mItemId;
	int mQuantity;
	bool mEmpty;
};