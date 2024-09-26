#include "Button.h"
#include "Core.h"

Button::Button(const sf::Sprite& sprite, const sf::Text& text, const sf::Vector2f& position)
	: mButtonSprite{ sprite }
	, mButtonText{ text }
	, mPosition{ position }
	, mButtonState{ BUTTONS::IDLE }
{
	mButtonSprite.setPosition(mPosition);
	CenterOrigin();
}

Button::Button(const sf::Sprite& sprite, const sf::Vector2f& position)
	: mButtonSprite{sprite}
	, mPosition{position}
	, mButtonState{ BUTTONS::IDLE }
{
	mButtonSprite.setPosition(mPosition);
	CenterOrigin();
}

void Button::SetHoverState(bool hoverState)
{
	mIsHoveringWhenPressed = hoverState;
}

void Button::SetClickCB(std::function<void()> clickCB)
{
	mClickCB = std::move(clickCB);
}

bool Button::GetHoverState() const
{
	return mIsHoveringWhenPressed;
}

sf::Vector2f Button::GetPosition() const
{
	return mPosition;
}

sf::Sprite& Button::GetSprite()
{
	return mButtonSprite;
}

sf::Text& Button::GetText()
{
	return mButtonText;
}

void Button::OnClick()
{
	if (mClickCB) { mClickCB(); }
}

void Button::CenterOrigin()
{
	sf::FloatRect spriteBounds = mButtonSprite.getLocalBounds();
	mButtonSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
	sf::FloatRect textBounds = mButtonText.getLocalBounds();
	mButtonText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f + 13.f);
	mButtonText.setPosition(mButtonSprite.getPosition());
}


// New Button functions

void Button::UpdateButtonState(const sf::Vector2f& mousePos, bool isClicked)
{
	if (mButtonSprite.getLocalBounds().contains(mousePos))
	{
		if (isClicked) { SetState(BUTTONS::CLICK); }
		else { SetState(BUTTONS::HOVER); }
	}
	else { SetState(BUTTONS::IDLE); }
}

void Button::SetState(BUTTONS::BUTTON_STATE state)
{
	mButtonState = state;
}

BUTTONS::BUTTON_STATE& Button::GetButtonState()
{
	return mButtonState;
}
