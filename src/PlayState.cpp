#include "PlayState.h"
#include "MainMenuState.h"
#include "Core.h"

PlayState::PlayState(System& system, ChangeStateCallback changeStateCB)
	:GameState{ system, changeStateCB }
{
}

void PlayState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
}

void PlayState::Exit()
{
	mSystem.InputMgr.RemoveObserver(this);
}

void PlayState::Update()
{
}

void PlayState::Draw()
{
}

void PlayState::OnMouseMove(int x, int y)
{
}

void PlayState::OnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape)
	{
		auto newState = std::make_unique<MainMenuState>(mSystem, mChangeStateCB);
		mChangeStateCB(std::move(newState));
	}
}

void PlayState::OnKeyRelease(sf::Keyboard::Key key)
{
}

void PlayState::OnMouseClick(sf::Mouse::Button button)
{
}

void PlayState::OnMouseRelease(sf::Mouse::Button button)
{
}
