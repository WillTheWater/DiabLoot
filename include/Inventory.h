#pragma once
#include "ItemSlot.h"
#include <array>
#include "Item.h"

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

	void									ToggleInventory();
	bool									isOpen();
	std::array<ItemSlot, 150>&				getItemSlots();
	std::array<sf::RectangleShape, 150>&	getSlotRects();
	bool									isMouseOverSlot();
	int										getMouseOverSlotIndex();
	sf::Vector2f							getLastMousePos();

	void									sortInventory();
	bool									addItem(Item& item);	// Returns false if there is no where to add the item to
	void									addGold(int quantity);
	int										getGold();
	bool									doesItemAlreadyHaveASlot(Item& item);
	size_t									getSlotForExistingItem(Item& item);
	bool									availabeSlot();
	size_t									getFirstOpenIndex();


private:
	std::array<ItemSlot, 150>				mItemSlots;
	std::array<sf::RectangleShape, 150>		mSlotRects;
	sf::Vector2f							mLastMousePos;
	bool									mMouseOver;
	int										mMouseOverSlotIndex;
	void									initialzeSlotRects();
	bool									mVisible = false;
	int										mGold;
};