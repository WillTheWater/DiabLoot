#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	enum class BUTTON_STATE
	{
		IDLE,
		HOVER,
		CLICK
	};

	Button(const sf::Vector2f& position);

	void									SetState(BUTTON_STATE newState);
	void									SetOrigin();
	Button::BUTTON_STATE					GetButtonState() const;
	sf::Vector2f							GetPosition() const;
	sf::FloatRect							GetButtonBounds() const;
	void									UpdateButtonState(const sf::Vector2f& mousePos, bool isClicked);

private:
	sf::Vector2f							mPosition;
	BUTTON_STATE							mButtonState;
};