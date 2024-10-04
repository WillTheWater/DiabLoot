#include "Merchant.h"
#include "SystemManager.h"

Merchant::Merchant(System& system)
	:mSystem{system}
	,mTotalFrames{8}
	,mCurrentPos{ 694.f,246.f }
	,mStartPos{694.f, 246.f}
	,mEndPos{978.f,456.f}
	,mRect{ {29.f, 68.f} }
	,mIsVisible{false}
	,mItem{ITEMID::MAX_ITEMS, ITEMRARITY::MAX_RARITIES}
	,mMousePos{0.f,0.f}
	,mDialogueOpen{false}
	,mIdleAnimFrame{0}
	,mWalkAnimFrame{0}
	,mWalkAnimProgress{0}
	,mWalking{true}
	,mWalkAnimStep{1.0f}
	,mIdleAnimStep{1.0f}
	,mIdleAnimProgress{0.f}
	,mWalkingProgress{0.f}
	,mWalkingIncrement{0.1f}
{
	mRect.setOrigin(mRect.getLocalBounds().getSize().x / 2, mRect.getLocalBounds().getSize().y);
}


void Merchant::OnMouseMove(int x, int y)
{
	mMousePos = { (float)x,(float)y };
	if (mRect.getGlobalBounds().contains(mMousePos))
	{
		mMouseOverMerchant = true;
	}
	else
	{
		mMouseOverMerchant = false;
	}

	if (mPurchaseButton.getGlobalBounds().contains(mMousePos) && mDialogueOpen)
	{
		mMouseOverPurchase = true;
	}
	else
	{
		mMouseOverPurchase = false;
	}
}

void Merchant::OnKeyPress(sf::Keyboard::Key key)
{
}

void Merchant::OnKeyRelease(sf::Keyboard::Key key)
{
}

void Merchant::OnMouseClick(sf::Mouse::Button button)
{
	
}

void Merchant::OnMouseRelease(sf::Mouse::Button button)
{
	if (mWalking) { return; }
	if (mMouseOverMerchant)
	{
		mDialogueOpen = !mDialogueOpen;
	}
	if (mMouseOverPurchase && mDialogueOpen)
	{
		int itemCost = CalculcateMissingItemCost();
		if (mSystem.InventoryMgr.GetGold() >= itemCost)
		{
			mDialogueOpen = false;
			mSystem.InventoryMgr.RemoveGold(itemCost);
			SpawnItem();
			UpdateItemToSell();
		}
	}
}

bool Merchant::IsVisible()
{
	return mIsVisible;
}

void Merchant::SetVisiblility(bool visibility)
{
	mIsVisible = visibility; 
}

std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> Merchant::GetItem()
{
	return mItem;
}

bool Merchant::IsWalking()
{
	return mWalking;
}

float Merchant::GetWalkAnimProgress()
{
	return mWalkAnimProgress;
}

float Merchant::GetIdleAnimProgress()
{
	return mIdleAnimProgress;
}

int Merchant::GetWalkFrame()
{
	float progressPerFrame = 1.0f / 8.f;
	return (int)(mWalkAnimProgress / progressPerFrame);
}

int Merchant::GetIdleFrame()
{
	float progressPerFrame = 1.0f / 8.f;
	return (int)(mIdleAnimProgress / progressPerFrame);
}

bool Merchant::IsDialogueOpen()
{
	return mDialogueOpen;
}

bool Merchant::IsMouseOverMerchant()
{
	return mMouseOverMerchant;
}

bool Merchant::IsMouseOverPurchase()
{
	return mMouseOverPurchase;
}

void Merchant::UpdateWalkingProgress()
{
	float deltaTime = mSystem.TimeMgr.GetDeltaTime();
	mWalkingProgress += mWalkingIncrement * deltaTime;
	if (mWalkingProgress > 1.0f)
	{
		mWalkingProgress = 1.0f;
		mWalking = false;
		InitializePurchaseButton();
	}
}

void Merchant::UpdateWalkPosition()
{
	mCurrentPos = mStartPos.lerpTo(mEndPos, mWalkingProgress);
	mRect.setPosition(mCurrentPos.getAsSFVec2F());
}

sf::Vector2f Merchant::GetCurrentPosition()
{
	return mCurrentPos.getAsSFVec2F();
}

sf::RectangleShape& Merchant::GetPurchaseButtonRect()
{
	return mPurchaseButton;
}

void Merchant::UpdateMerchant()
{
	if (mWalking)
	{
		UpdateWalkingProgress();
		IncremenentWalkAnimation();
		UpdateWalkPosition();
	}
	else
	{
		IncremenentIdleAnimation();
	}

	UpdateItemToSell();
}

void Merchant::UpdateItemToSell()
{
	mItem = mSystem.InventoryMgr.GetMissingItem();
}

int Merchant::CalculcateMissingItemCost()
{
	return (ITEMGEN::TOTAL_UNIQUE_ITEMS - mSystem.InventoryMgr.GetNumberOfItemsMissing()) * 10000;
}

void Merchant::IncremenentWalkAnimation()
{
	mWalkAnimProgress += mWalkAnimStep * mSystem.TimeMgr.GetDeltaTime();
	if (mWalkAnimProgress > 1.0f)
	{
		mWalkAnimProgress = 0.f;
	}
}

void Merchant::IncremenentIdleAnimation()
{
	mIdleAnimProgress += mIdleAnimStep * mSystem.TimeMgr.GetDeltaTime();
	if (mIdleAnimProgress > 1.0f)
	{
		mIdleAnimProgress = 0.f;
	}
}

void Merchant::SpawnItem()
{
	mSystem.LevelMgr.GetCurrentLevel().SpawnSingleParticle(mCurrentPos.getAsSFVec2F(), mItem);
}

void Merchant::Speak()
{

}

void Merchant::InitializePurchaseButton()
{
	mPurchaseButton.setSize({ 65.f, 65.f });
	mPurchaseButton.setPosition(mCurrentPos.getAsSFVec2F() + sf::Vector2f{30.f, -120.f});
}
