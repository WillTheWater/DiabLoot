#include "Button.h"
#include "Button.h"

Button::Button(const sf::Vector2f& position)
	: mPosition{position}
	, mButtonType{BUTTON_TYPE::WIDE}
	, mButtonState{BUTTON_STATE::IDLE}
{
}

void Button::SetButtonType(BUTTON_TYPE newType)
{
	mButtonType = newType;
}

void Button::SetButtonState(BUTTON_STATE newState)
{
	mButtonState = newState;
}

Button::BUTTON_TYPE Button::GetButtonType() const
{
	return mButtonType;
}

Button::BUTTON_STATE Button::GetButtonState() const
{
	return mButtonState;
}

sf::FloatRect Button::GetButtonBounds(const sf::Vector2f& position) const
{
	sf::FloatRect buttonBounds;
	if (mButtonType == BUTTON_TYPE::WIDE) { buttonBounds = sf::FloatRect(position.x, position.y, 600.f, 83.f); }
	else if (mButtonType == BUTTON_TYPE::SQUARE) { buttonBounds = sf::FloatRect(position.x, position.y, 65.f, 65.f); }
	return buttonBounds;
}

sf::Vector2f Button::GetPosition() const
{
	return mPosition;
}