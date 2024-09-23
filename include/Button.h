#pragma once
#include <string>
#include <functional>
#include <SFML/Graphics.hpp>

class Button
{
public:

	enum class BUTTON_TYPE
	{
		WIDE,
		SQUARE
	};

	enum class BUTTON_STATE
	{
		IDLE,
		HOVER,
		CLICK
	};

	Button(const sf::Vector2f& position);
	Button(const sf::Vector2f& position, const std::string& buttonText, const sf::Font& font);

	void									SetButtonType(BUTTON_TYPE newType);
	void									SetButtonState(BUTTON_STATE newState);
	void									SetHoverState(bool hoverState);
	void									SetClickCB(std::function<void()> clickCB);
	bool									GetHoverState() const;
	Button::BUTTON_TYPE						GetButtonType() const;
	Button::BUTTON_STATE					GetButtonState() const;
	sf::FloatRect							GetButtonBounds(const sf::Vector2f& position) const;
	sf::Vector2f							GetPosition() const;
	void									OnClick();

private:
	std::string								mButtonText;
	sf::Font								mButtonFont;
	sf::Text								mButtonPrintText;
	sf::Vector2f							mPosition;
	bool									mIsHoveringWhenPressed;
	BUTTON_STATE							mButtonState;
	BUTTON_TYPE								mButtonType;
	std::function<void()>					mClickCB;
};