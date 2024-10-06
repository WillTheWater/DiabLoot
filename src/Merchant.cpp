#include "Merchant.h"
#include "SystemManager.h"

Merchant::Merchant(System& system)
	:mSystem{system}
	,mTotalFrames{8}
	,mCurrentPos{ 694.f,246.f }
	,mStartPos{898.f, 314.f}
	,mEndPos{992.f,394.f}
	,mRect{ {38.f, 92.f} }
	,mIsVisible{false}
	,mItem{ITEMID::MAX_ITEMS, ITEMRARITY::MAX_RARITIES}
	,mLastSoldItem{ITEMID::MAX_ITEMS, ITEMRARITY::MAX_RARITIES}
	,mMousePos{0.f,0.f}
	,mIdleAnimFrame{0}
	,mWalkAnimFrame{0}
	,mWalkAnimProgress{0}
	,mWalking{true}
	,mWalkAnimStep{1.3f}
	,mIdleAnimStep{1.0f}
	,mIdleAnimProgress{0.f}
	,mWalkingProgress{0.f}
	,mWalkingIncrement{0.40f}
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
		if (mItem == mLastSoldItem)
		{
			return;
		}
		int itemCost = CalculcateMissingItemCost();
		if (mSystem.InventoryMgr.GetGold() >= itemCost)
		{
			mSystem.InventoryMgr.RemoveGold(itemCost);
			SpawnItem();
			mLastSoldItem = mItem;
			UpdateItemToSell();
			PurchaseAudio();
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


bool Merchant::IsMouseOverMerchant()
{
	return mMouseOverMerchant;
}

void Merchant::UpdateWalkingProgress()
{
	float deltaTime = mSystem.TimeMgr.GetDeltaTime();
	mWalkingProgress += mWalkingIncrement * deltaTime;
	if (mWalkingProgress > 1.0f)
	{
		mWalkingProgress = 1.0f;
		mWalking = false;
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
	return (6 - (ITEMGEN::TOTAL_UNIQUE_ITEMS - mSystem.InventoryMgr.GetNumberOfUniqueItems())) * 100000;
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
	mSystem.LevelMgr.GetCurrentLevel().SpawnMerchantParticle(mCurrentPos.getAsSFVec2F(), mItem);
}

void Merchant::ArrivalAudio()
{
	if (!mFirstAppearance)
	{
		SoundManager::GetInstance().PlayASound(PLAYSOUND::INTRO, 25.f, 1.0f, false);
		mFirstAppearance = true;
	}
	else
	{
		int itemsMissing = ITEMGEN::TOTAL_UNIQUE_ITEMS - mSystem.InventoryMgr.GetNumberOfUniqueItems();
		switch (itemsMissing)
		{
		case 1: SoundManager::GetInstance().PlayASound(PLAYSOUND::INSULT, 25.f, 1.0f, false); break;
		case 2: SoundManager::GetInstance().PlayASound(PLAYSOUND::HAPPY, 25.f, 1.0f, false); break;
		default: SoundManager::GetInstance().PlayASound(PLAYSOUND::GOODTOSEEYOU, 25.f, 1.0f, false); break;
		}		
	}
	
}

void Merchant::PurchaseAudio()
{
	int random = MathU::Random(1, 2);
	StopAllGheedAudio();
	if (random == 1)
	{
		SoundManager::GetInstance().PlayASound(PLAYSOUND::FAREWELL, 25.f, 1.0f, false);
	}
	else
	{
		SoundManager::GetInstance().PlayASound(PLAYSOUND::LAUGH, 25.f, 1.0f, false);
	}
}

void Merchant::ResetMerchant()
{
	mIsVisible = false;
	mWalkingProgress = 0.f;
	mWalkAnimProgress = 0.f;
	mWalking = true;
	mCurrentPos = mStartPos;
}

void Merchant::StopAllGheedAudio()
{
	SoundManager::GetInstance().StopPlayingSound(PLAYSOUND::INTRO);
	SoundManager::GetInstance().StopPlayingSound(PLAYSOUND::INSULT);
	SoundManager::GetInstance().StopPlayingSound(PLAYSOUND::HAPPY);
	SoundManager::GetInstance().StopPlayingSound(PLAYSOUND::GOODTOSEEYOU);
	SoundManager::GetInstance().StopPlayingSound(PLAYSOUND::FAREWELL);
	SoundManager::GetInstance().StopPlayingSound(PLAYSOUND::LAUGH);
}
