#pragma once
#include "Assets.h"
#include <utility>
#include "SFML/Graphics.hpp"

namespace ItemTexts
{
	
}

class Item
{
public:
	// Constructors
	Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, sf::Vector2f pos, sf::Text& text, int quantity = 1);

private:
	ITEMID::ITEM mId;
	ITEMRARITY::RARITY mRarity;
	sf::RectangleShape mRect;
	int mQuantity;
	sf::Vector2f mPos;
	sf::Text& mText;
};