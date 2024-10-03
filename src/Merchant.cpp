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
	,mWalkSpeed{45.0f}
	,mIdleAnimProgress{0.f}
{
	mWalkVector = mStartPos + mEndPos;
	mWalkVector = mWalkVector / mWalkVector.magnitude();
	mRect.setOrigin(mRect.getLocalBounds().getSize().x / 2, mRect.getLocalBounds().getSize().y);
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

void Merchant::UpdateWalkPosition()
{
	float deltaTime = mSystem.TimeMgr.GetDeltaTime();
	float travelDistance = (mWalkVector * (mWalkSpeed * deltaTime)).magnitude();
	if (mCurrentPos.distance(mEndPos) > travelDistance)
	{
		mCurrentPos += mWalkVector * (mWalkSpeed * deltaTime);
	}
	else
	{
		mCurrentPos = mEndPos; 
		mWalking = false;
	}
}

sf::Vector2f Merchant::GetCurrentPosition()
{
	return mCurrentPos.getAsSFVec2F();
}

void Merchant::UpdateMerchant()
{
	if (mWalking)
	{
		IncremenentWalkAnimation();
		UpdateWalkPosition();
	}
	else
	{
		IncremenentIdleAnimation();
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
	return (10 - mSystem.InventoryMgr.GetNumberOfItemsMissing()) * 100000;
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
