#include "Item.h"

Item::Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, sf::Vector2f pos, sf::Text& text, int quantity)
	:mId{item.first}
	,mRarity{item.second}
	,mQuantity{quantity}
	,mPos{pos}
	,mText{text}
{
	mRect.setSize({ mText.getLocalBounds().getSize().x, mText.getLocalBounds().getSize().y });
	mRect.setOrigin(mRect.getSize().x / 2, mRect.getSize().y / 2);
}