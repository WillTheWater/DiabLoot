#include "Item.h"
#include "MathUtilities.h"
#include "SoundManager.h"

Item::Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int unique, sf::Vector2f pos, sf::Text& text, std::function<void(Item&)> callback, int quantity)
	:mItemId{item.first}
	,mUniqueId{unique}
	,mRarity{item.second}
	,mQuantity{quantity}
	,mPos{pos}
	,mText{text}
	,mRect{ {100.f,100.f} }
	,mCallback{callback}
{
	if (mItemId == ITEMID::GOLD)
	{
		mText.setString(std::to_string(quantity) + ' ' + mText.getString());
	}
	mRect.setSize({ mText.getGlobalBounds().getSize().x + FONTS::PADDING, mText.getGlobalBounds().getSize().y + FONTS::PADDING });
	mRect.setOrigin(mRect.getGlobalBounds().width / 2, mRect.getGlobalBounds().height / 2 + FONTS::ORIGIN_YOFFSET);
	mRect.setPosition(pos);
}

Item::Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int quantity) // DEBUG ONLY
	:mItemId{ item.first }
	, mUniqueId{ 0 }
	, mRarity{ item.second }
	, mQuantity{ quantity }
	, mPos{ sf::Vector2f{0.f,0.f} }
	, mText{}
	, mRect{ {100.f,100.f} }
	, mCallback{ nullptr }
{
}

// Observer overrides
void Item::OnMouseMove(int x, int y) 
{	 
	sf::Vector2f mousePos(x, y);
	mMouseLastPos = mousePos;
}	 
	 
void Item::OnKeyPress(sf::Keyboard::Key key) 
{	 
	 
}	 
	 
void Item::OnKeyRelease(sf::Keyboard::Key key) 
{	 
	 
}	 
	 
void Item::OnMouseClick(sf::Mouse::Button button) 
{	 
	if (mRect.getGlobalBounds().contains(mMouseLastPos))
	{
		mCallback(*this);
		auto pitchShifter = MathU::Random(0.9f, 1.1f);
		auto modulator = MathU::Random(10.f, 30.f);
		SoundManager::GetInstance().PlaySound(PLAYSOUND::ITEM_PICKUP, modulator, pitchShifter);
	}
}	 
	 
void Item::OnMouseRelease(sf::Mouse::Button button) 
{

}

sf::Vector2f Item::GetPosition()
{
	return mPos;
}

sf::RectangleShape Item::GetTextRect()
{
	return mRect;
}

int Item::GetUniqueId()
{
	return mUniqueId;
}

sf::Text& Item::GetItemText()
{
	return mText;
}

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> Item::GetItemID()
{
	return { mItemId, mRarity };
}

int Item::GetQuantity()
{
	return mQuantity;
}

void Item::SetTextRect(sf::RectangleShape& rect)
{
	mRect = rect;
}