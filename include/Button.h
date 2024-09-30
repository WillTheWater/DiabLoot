#pragma once
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Assets.h"

class Button
{
public:
	
	Button(const sf::Sprite& sprite, const sf::Text& text, const sf::Vector2f& position);
	Button(const sf::Sprite& sprite, const sf::Vector2f& position);

	sf::Vector2f							GetPosition() const;
	sf::Sprite&								GetSprite();
	sf::Text&								GetText();
	BUTTONS::BUTTON_STATE&					GetButtonState();
	void									CenterOrigin();
	void									SetClickCB(std::function<void()> clickCB);
	void									SetState(BUTTONS::BUTTON_STATE state);
	void									HandleEvent(sf::Vector2f mousePos, bool isClicked);
	void									OnClick();
	void									SetScale(float scale);

private:
	sf::Sprite								mButtonSprite;
	sf::Text								mButtonText;
	sf::Vector2f							mPosition;
	std::function<void()>					mClickCB;
	BUTTONS::BUTTON_STATE					mButtonState;
	bool									IsButtonDown;
	void									OnButtonUp();
	void									OnButtonDown();
	void									OnButtonHover();
};