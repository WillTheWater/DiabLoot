#pragma once
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

	void									SetButtonType(BUTTON_TYPE newType);
	void									SetButtonState(BUTTON_STATE newState);
	Button::BUTTON_TYPE						GetButtonType() const;
	Button::BUTTON_STATE					GetButtonState() const;
	sf::FloatRect							GetButtonBounds(const sf::Vector2f& position) const;
	sf::Vector2f							GetPosition() const;

private:
	sf::Vector2f							mPosition;
	BUTTON_STATE							mButtonState;
	BUTTON_TYPE								mButtonType;
};