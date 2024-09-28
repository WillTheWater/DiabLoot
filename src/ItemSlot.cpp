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

ItemSlot::ItemSlot(int id, int rarity, int quantity)
	:ItemSlot::ItemSlot(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>{(ITEMID::ITEM)id, (ITEMRARITY::RARITY)rarity}, quantity)
{
	if (mItemId.first == ITEMID::MAX_ITEMS)
	{
		mEmpty = true;
	}
}

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> ItemSlot::getItemId()
{
	return mItemId;
}

bool ItemSlot::operator==(const ItemSlot& other)
{
	return (
		this->mItemId.first == other.mItemId.first
		&&
		this->mItemId.second == other.mItemId.second
		&&
		this->mQuantity == other.mQuantity
		&&
		this->mEmpty == other.mEmpty
		);
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

