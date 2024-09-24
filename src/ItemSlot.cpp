#include "ItemSlot.h"

ItemSlot::ItemSlot()
	:mEmpty{ true }
	,mQuantity{0}
	,mItemId{ITEMID::MAX_ITEMS, ITEMRARITY::MAX_RARITIES}
{
}

ItemSlot::ItemSlot(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity)
	:mEmpty{ false }
	, mItemId{ item }
	, mQuantity{ quantity }
{
}

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> ItemSlot::getItemId()
{
	return mItemId;
}

bool ItemSlot::isEmpty()
{
	return mEmpty;
}

int ItemSlot::getQuantity()
{
	return mQuantity;
}

void ItemSlot::incrementQuantity(int amount)
{
	mQuantity += amount;
}

void ItemSlot::setContainedItem(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity)
{
	mItemId = item;
	mQuantity = quantity; 
	mEmpty = false;
}

void ItemSlot::toggleEmpty(bool empty)
{
	mEmpty = empty;
	mQuantity = 0;
	mItemId = { ITEMID::MAX_ITEMS, ITEMRARITY::MAX_RARITIES };
}

