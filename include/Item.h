#pragma once
#include "Assets.h"
#include <utility>
#include "SFML/Graphics.hpp"
#include "InputManager.h"
#include <functional>

namespace ItemTexts
{
	
}

class Item : public InputObserver
{
public:
	// Constructors
	Item(std::pair<ITEMID::ITEM, ITEMRARITY::RARITY> item, int unique, sf::Vector2f pos, sf::Text& text, std::function<void(Item&)> callback, int quantity = 1);

	// Observer overrides
	void								OnMouseMove(int x, int y) override;
	void								OnKeyPress(sf::Keyboard::Key key) override;
	void								OnKeyRelease(sf::Keyboard::Key key) override;
	void								OnMouseClick(sf::Mouse::Button button) override;
	void								OnMouseRelease(sf::Mouse::Button button) override;

	// Getters

	sf::Vector2f									getPosition();
	sf::RectangleShape								getTextRect();
	std::pair<ITEMID::ITEM, ITEMRARITY::RARITY>		getItemID();
	int												getQuantity();
	int												getUniqueId();
	// Setters
	void											setTextRect(sf::RectangleShape& rect);

private:
	int mUniqueId;
	ITEMID::ITEM mItemId;
	ITEMRARITY::RARITY mRarity;
	sf::RectangleShape mRect;
	int mQuantity;
	sf::Vector2f mPos;
	sf::Text& mText;
	std::function<void(Item&)> mCallback;
	sf::Vector2f mMouseLastPos;
};