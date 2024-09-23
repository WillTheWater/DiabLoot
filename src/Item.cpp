#include "Item.h"

Item::Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, sf::Vector2f pos, sf::Text& text, int quantity)
	:mId{item.first}
	,mRarity{item.second}
	,mQuantity{quantity}
	,mPos{pos}
	,mText{text}
	,mRect{ {100.f,100.f} }
{
	mRect.setSize({ mText.getGlobalBounds().getSize().x + 8.f, mText.getGlobalBounds().getSize().y + 8.f});
	mRect.setOrigin(mRect.getGlobalBounds().width / 2, mRect.getGlobalBounds().height / 2 - 5.f);
	mRect.setPosition(pos);
	mRect.move(0, -30);
}

sf::Vector2f Item::getPosition()
{
	return mPos;
}

sf::RectangleShape Item::getTextRect()
{
	return mRect;
}

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> Item::getItemID()
{
	return { mId, mRarity };
}

int Item::getQuantity()
{
	return mQuantity;
}
