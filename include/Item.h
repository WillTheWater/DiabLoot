#pragma once
#include "Assets.h"
#include <utility>
#include "SFML/Graphics.hpp"

class Item
{
public:
	// Constructors
	Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity = 1);
	Item(ITEMID::ITEM id, ITEMRARITY::RARITY rarity, int quantity = 1);

private:
	ITEMID::ITEM mId;
	ITEMRARITY::RARITY mRarity;
	sf::RectangleShape mRect;
	int mQuantity;
};