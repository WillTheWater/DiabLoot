#include "Merchant.h"

Merchant::Merchant(System& system)
	:mSystem{system}
	,mIsVisible{false}
	,mItem{ITEMID::MAX_ITEMS, ITEMRARITY::MAX_RARITIES}
	,mMousePos{0.f,0.f}
{
}


void Merchant::OnMouseMove(int x, int y)
{
	mMousePos =  {(float)x,(float)y};
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
	if (mRect.getGlobalBounds().contains(mMousePos))
	{
		mDialogueOpen = !mDialogueOpen;
	}
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

bool Merchant::IsDialogueOpen()
{
	return mDialogueOpen;
}

void Merchant::UpdateMerchant()
{
	if (mWalking)
	{
		IncremenentWalkAnimation();
	}
	else
	{
		IncremenentWalkAnimation();
	}

	UpdateItemToSell();
	CalculcateMissingItemCost();
}

void Merchant::UpdateItemToSell()
{
	mItem = mSystem.InventoryMgr.GetMissingItem();
}

int Merchant::CalculcateMissingItemCost()
{
	return 0;
}

void Merchant::IncremenentWalkAnimation()
{
	mWalkAnimProgress += mWalkAnimStep * mSystem.TimeMgr.GetDeltaTime();
	if (mWalkAnimStep > 1.0f)
	{
		mWalkAnimStep = 0.f;
		mWalking = false;
	}

}

void Merchant::SpawnItem()
{
	mSystem.LevelMgr.GetCurrentLevel().SpawnSingleParticle(mPos, mItem);
}
