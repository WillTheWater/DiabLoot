#include "Button.h"

Button::Button(const sf::Vector2f& position)
	: mPosition{position}
	, mButtonState{BUTTON_STATE::IDLE}
{
}

void Button::SetState(BUTTON_STATE newState)
{
	mButtonState = newState;
}

Button::BUTTON_STATE Button::GetButtonState() const
{
	return mButtonState;
}

sf::Vector2f Button::GetPosition() const
{
	return mPosition;
}

sf::FloatRect Button::GetButtonBounds() const
{
	return sf::FloatRect(mPosition.x, mPosition.y, 0.f, 0.f);
}

void Button::UpdateButtonState(const sf::Vector2f& mousePos, bool isClicked)
{
	if (GetButtonBounds().contains(mousePos))
	{
		if (isClicked) { SetState(BUTTON_STATE::CLICK); }
		else { SetState(BUTTON_STATE::HOVER); }
	}
	else { SetState(BUTTON_STATE::IDLE); }
}