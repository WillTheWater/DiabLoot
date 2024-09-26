#include "PlayState.h"
#include "MainMenuState.h"
#include "Core.h"

PlayState::PlayState(System& system, ChangeStateCallback changeStateCB, Level& level)
	:GameState{ system, changeStateCB }
	,mLevel{level}

{
}

void PlayState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
	// WHY DOES THIS FIX THE PROBLEM!!!!!
	//mLevel.EnterLevel();
	//mLevel.ExitLevel();
	mLevel.EnterLevel();
}

void PlayState::Exit()
{
	mSystem.InputMgr.RemoveObserver(this);
	mLevel.ExitLevel();
}

void PlayState::Update()
{
	mLevel.UpdateLevel();
}

void PlayState::Draw()
{
	mSystem.RenderMgr.RenderLevel(mLevel);
	mSystem.RenderMgr.PlayStateRender();
}

void PlayState::OnMouseMove(int x, int y)
{
}

void PlayState::OnKeyPress(sf::Keyboard::Key key)
{
	
}

void PlayState::OnKeyRelease(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::R)
	{
		auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel());
		mChangeStateCB(std::move(newState));
	}
	if (key == sf::Keyboard::Escape)
	{
		if (mSystem.InventoryMgr.isOpen()) { mSystem.InventoryMgr.ToggleInventory(); }
		else
		{
			auto newState = std::make_unique<MainMenuState>(mSystem, mChangeStateCB);
			mChangeStateCB(std::move(newState));
		}
	}
	if (key == sf::Keyboard::I)
	{
		mSystem.InventoryMgr.ToggleInventory();
	}
}

void PlayState::OnMouseClick(sf::Mouse::Button button)
{
}

void PlayState::OnMouseRelease(sf::Mouse::Button button)
{
}
