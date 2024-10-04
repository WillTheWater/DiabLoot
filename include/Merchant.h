#pragma once
#include "Inventory.h"
#include "InputManager.h"
#include "Vec2.h"

class System;

class Merchant : public InputObserver
{
public:
	Merchant(System& system);

	virtual void							OnMouseMove(int x, int y);
	virtual void							OnKeyPress(sf::Keyboard::Key key);
	virtual void							OnKeyRelease(sf::Keyboard::Key key);
	virtual void							OnMouseClick(sf::Mouse::Button button);
	virtual void							OnMouseRelease(sf::Mouse::Button button);

	bool										IsVisible();
	void										SetVisiblility(bool visibility);
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> GetItem();
	bool										IsWalking();
	float										GetWalkAnimProgress();
	float										GetIdleAnimProgress();
	int											GetWalkFrame();
	int											GetIdleFrame();
	bool										IsMouseOverMerchant();
	void										UpdateWalkingProgress();
	void										UpdateWalkPosition();
	sf::Vector2f								GetCurrentPosition();
	void									UpdateMerchant();
	void									UpdateItemToSell();
	int										CalculcateMissingItemCost();
	void									IncremenentWalkAnimation();
	void									IncremenentIdleAnimation();
	void									SpawnItem();
	void									ArrivalAudio();
	void									PurchaseAudio();
	void									ResetMerchant();
	void									StopAllGheedAudio();



private: 
	bool mIsVisible;
	Vec2 mCurrentPos;
	Vec2 mStartPos;
	Vec2 mEndPos;
	sf::RectangleShape mRect;
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> mItem; 
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> mLastSoldItem; 
	float mWalkingProgress;
	float mWalkingIncrement;
	bool mWalking;
	float mWalkAnimProgress;
	float mWalkAnimStep; 
	int mWalkAnimFrame;
	float mIdleAnimProgress;
	float mIdleAnimStep;
	int mIdleAnimFrame;
	sf::Vector2f mMousePos; 
	System& mSystem;
	int mTotalFrames;

	bool mMouseOverMerchant = false; 
	bool mFirstAppearance = false;


};