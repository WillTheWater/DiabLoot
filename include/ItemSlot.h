#pragma once
#include "Assets.h"
#include <utility>

class ItemSlot
{
public:
	ItemSlot();
	ItemSlot(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity);

	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> getItemId();
	bool										isEmpty();
	int											getQuantity();
	void										incrementQuantity(int amount = 1);

	void										setContainedItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity = 1);
	void										toggleEmpty(bool empty);

private:
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> mItemId;
	int mQuantity;
	bool mEmpty;
};