#pragma once
#include "Inventory.h"
#include "InputManager.h"
#include "SystemManager.h"

class Merchant : public InputObserver
{
public:
	Merchant(System& system);

	virtual void							OnMouseMove(int x, int y);
	virtual void							OnKeyPress(sf::Keyboard::Key key);
	virtual void							OnKeyRelease(sf::Keyboard::Key key);
	virtual void							OnMouseClick(sf::Mouse::Button button);
	virtual void							OnMouseRelease(sf::Mouse::Button button);

	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> GetItem();
	bool										IsWalking();
	float										GetWalkAnimProgress();
	float										GetIdleAnimProgress();
	bool										IsDialogueOpen();

	void									UpdateMerchant();
	void									UpdateItemToSell();
	int										CalculcateMissingItemCost();
	void									IncremenentWalkAnimation();
	void									SpawnItem();



private: 
	bool mIsVisible;
	sf::Vector2f mPos;
	sf::RectangleShape mRect;
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> mItem; 
	bool mWalking;
	float mWalkAnimProgress;
	float mWalkAnimStep; 
	int mWalkAnimFrame;
	float mIdleAnimProgress;
	float mIdleAnimStep;
	int mIdleAnimFrame;
	bool mDialogueOpen;
	sf::Vector2f mMousePos; 
	System& mSystem;

};