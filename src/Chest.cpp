#include "Chest.h"
#include "SoundManager.h"
#include "MathUtilities.h"

Chest::Chest(sf::Vector2f position, bool mirrored, std::function<void(Chest&)> callback)
	:mPos{position}
	,mRect{ {50.f,60.f} }
	,mMirrored{mirrored}
	,mOpened{false}
	,mMouseOver{false}
	,mCallback{callback}
{
	mRect.setOrigin(mRect.getSize().x / 2.f, mRect.getSize().y / 2.f);
	mRect.setPosition(mPos);
}

void Chest::OnMouseMove(int x, int y)
{
	sf::Rect bound = mRect.getGlobalBounds();
	sf::Vector2f mousePos (x, y);
	if (bound.contains(mousePos))
	{
		mMouseOver = true;
	}
	else
	{
		mMouseOver = false;
	}
}

void Chest::OnKeyPress(sf::Keyboard::Key key)
{
}

void Chest::OnKeyRelease(sf::Keyboard::Key key)
{
}

void Chest::OnMouseClick(sf::Mouse::Button button)
{
	if (mMouseOver && !mOpened)
	{
		OpenChest();
	}
}

void Chest::OnMouseRelease(sf::Mouse::Button button)
{
}

void Chest::ResetChest()
{
	mOpened = false;
}

void Chest::OpenChest()
{
	mOpened = true; 
	mCallback(*this);
	auto pitchShifter = MathU::Random(0.8f, 1.2f);
	auto modulator = MathU::Random(20.f, 40.f);
	SoundManager::GetInstance().PlaySound(PLAYSOUND::OPEN_CHEST, modulator, pitchShifter);
}

sf::Vector2f Chest::GetPosition() const
{
	return mPos;
}

bool Chest::IsOpened() const
{
	return mOpened;
}

bool Chest::IsMirrored() const
{
	return mMirrored;
}


