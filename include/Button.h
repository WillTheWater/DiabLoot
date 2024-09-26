#pragma once
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:

	
	Button(const sf::Sprite& sprite, const sf::Text& text, const sf::Vector2f& position);
	Button(const sf::Sprite& sprite, const sf::Vector2f& position);

	void									SetHoverState(bool hoverState);
	void									SetClickCB(std::function<void()> clickCB);
	bool									GetHoverState() const;
	sf::Vector2f							GetPosition() const;
	sf::Sprite&								GetSprite();
	sf::Text&								GetText();
	void									OnClick();
	void									CenterOrigin();



private:
	sf::Sprite								mButtonSprite;
	sf::Text								mButtonText;
	sf::Vector2f							mPosition;
	bool									mIsHoveringWhenPressed;
	std::function<void()>					mClickCB;
};