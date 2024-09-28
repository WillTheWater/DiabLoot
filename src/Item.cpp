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

sf::Vector2f Item::getPosition()
{
	return mPos;
}

sf::RectangleShape Item::getTextRect()
{
	return mRect;
}

int Item::getUniqueId()
{
	return mUniqueId;
}

sf::Text& Item::getItemText()
{
	return mText;
}

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> Item::getItemID()
{
	return { mItemId, mRarity };
}

int Item::getQuantity()
{
	return mQuantity;
}

void Item::setTextRect(sf::RectangleShape& rect)
{
	mRect = rect;
}