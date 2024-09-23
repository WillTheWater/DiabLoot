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

	// Getters

	sf::Vector2f									getPosition();
	sf::RectangleShape								getTextRect();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>		getItemID();
	int												getQuantity();

private:
	ITEMID::ITEM mId;
	ITEMRARITY::RARITY mRarity;
	sf::RectangleShape mRect;
	int mQuantity;
	sf::Vector2f mPos;
	sf::Text& mText;
};