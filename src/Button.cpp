#include "Button.h"
#include "SoundManager.h"
#include "Core.h"

Button::Button(const sf::Sprite& sprite, const sf::Text& text, const sf::Vector2f& position)
	: mButtonSprite{ sprite }
	, mButtonText{ text }
	, mPosition{ position }
	, mButtonState{ BUTTONS::IDLE }
	, IsButtonDown{false}
{
	mButtonSprite.setPosition(mPosition);
	CenterOrigin();
}

Button::Button(const sf::Sprite& sprite, const sf::Vector2f& position)
	: mButtonSprite{sprite}
	, mPosition{position}
	, mButtonState{ BUTTONS::IDLE }
	, IsButtonDown{ false }
{
	mButtonSprite.setPosition(mPosition);
	CenterOrigin();
}

void Button::SetClickCB(std::function<void()> clickCB)
{
	mClickCB = std::move(clickCB);
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
	// Retrieve the current audio state from SoundManager
	AUDIO_MUTE::AUDIOSTATE currentAudioState = SoundManager::GetInstance().GetAudioState();

	if (currentAudioState == AUDIO_MUTE::AUDIOSTATE::UNMUTED ||
		currentAudioState == AUDIO_MUTE::AUDIOSTATE::MUTE_MUSIC)
	{
		// Play the button click sound if audio is not fully muted
		SoundManager::GetInstance().PlaySound(PLAYSOUND::BUTTON_DOWN);
	}
}

void Button::SetScale(float scale)
{
	mButtonSprite.setScale(scale, scale);
	mButtonText.setScale(scale, scale);
}

void Button::CenterOrigin()
{
	sf::FloatRect spriteBounds = mButtonSprite.getLocalBounds();
	mButtonSprite.setOrigin(spriteBounds.width / 2.f, spriteBounds.height / 2.f);
	sf::FloatRect textBounds = mButtonText.getLocalBounds();
	mButtonText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f + 13.f);
	mButtonText.setPosition(mButtonSprite.getPosition());
}

void Button::SetState(BUTTONS::BUTTON_STATE state)
{
	mButtonState = state;
}

BUTTONS::BUTTON_STATE& Button::GetButtonState()
{
	return mButtonState;
}

void Button::OnButtonUp()
{
	IsButtonDown = false;
	mButtonSprite.setColor(sf::Color{ 200, 200, 200, 255 });
}

void Button::OnButtonDown()
{
	IsButtonDown = true;
}

void Button::OnButtonHover()
{
	mButtonSprite.setColor(sf::Color{ 200, 200, 200, 255 });
}

void Button::HandleEvent(sf::Vector2f mousePos, bool isClicked)
{
	bool isHovering = mButtonSprite.getGlobalBounds().contains(mousePos);
	if (isHovering)
	{
		if (isClicked) { SetState(BUTTONS::CLICK); OnButtonDown(); }
		else { SetState(BUTTONS::HOVER); }
	}
	else { SetState(BUTTONS::IDLE); }
	switch (mButtonState)
	{
	case BUTTONS::BUTTON_STATE::HOVER:
		mButtonSprite.setColor(sf::Color{ 200, 200, 200, 255 });  // Set color for hover
		break;
	case BUTTONS::BUTTON_STATE::CLICK:
		mButtonSprite.setColor(sf::Color{ 100, 100, 100, 255 });  // Set color for click
		break;
	default:
		mButtonSprite.setColor(sf::Color{ 255, 255, 255, 255 });  // Set color for idle
		break;
	}
	if (IsButtonDown && !isHovering) { OnButtonUp(); }
	if (isHovering && IsButtonDown && !isClicked) { OnClick(); OnButtonUp(); }
}