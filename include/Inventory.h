#pragma once
#include "ItemSlot.h"
#include <array>
#include "Item.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>
#include "ItemGenerator.h"
#include <map>

class Inventory : public InputObserver
{
public:
	Inventory();

	// Observer overrides
	void									OnMouseMove(int x, int y) override;
	void									OnKeyPress(sf::Keyboard::Key key) override;
	void									OnKeyRelease(sf::Keyboard::Key key) override;
	void									OnMouseClick(sf::Mouse::Button button) override;
	void									OnMouseRelease(sf::Mouse::Button button) override;
	void									SwapSlots(int a, int b);
	size_t									GetFirstOpenIndex();
	int										GetClickedDownIndex() const;
	bool									IsItemSlotClicked() const;
	ITEMID::ITEM							GetItemIdOfSlotClicked();

	void									ToggleInventory();
	void									ToggleItemMissingList();
	bool									IsOpen() const;
	bool									IsItemListOn();
	std::array<ItemSlot, 150>&				getItemSlots();
	std::array<sf::RectangleShape, 150>&	getSlotRects();
	bool									IsMouseOverSlot() const;
	int										GetMouseOverSlotIndex() const;
	sf::Vector2f							GetLastMousePos() const;
	bool									AddItem(Item& item);	// Returns false if there is no where to add the item to
	void									AddGold(int quantity);
	void									RemoveGold(int quantity);
	int										GetGold();
	bool									DoesItemAlreadyHaveASlot(Item& item);
	size_t									GetSlotForExistingItem(Item& item);
	bool									AvailabeSlot();

	void									SortInventory();
	void									LoadInventory();
	void									SaveInventory();
	void									DeleteInventory();
	int										GetNumberOfUniqueItems();
	bool									HasOneOfEverything();	// Returns true if win condition is met
	void									DebugGetOneOfEverything();
	void									InitializeItemFoundList();
	std::map<std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>, bool>& GetItemFoundList();


private:
	std::array<ItemSlot, 150>				mItemSlots;
	std::array<sf::RectangleShape, 150>		mSlotRects;
	sf::Vector2f							mLastMousePos;
	bool									mMouseOver;
	int										mMouseOverSlotIndex;
	void									InitialzeSlotRects();
	bool									mVisible = false;
	int										mGold;
	int										mClickedDownIndex;
	int										mClickedReleaseIndex;
	std::map<std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>, bool>	mItemsFound;
	bool									mItemsMissingDisplay;

};