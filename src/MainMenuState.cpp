#include "MainMenuState.h"
#include "PlayState.h"
#include "Core.h"

MainMenuState::MainMenuState(System& system, ChangeStateCallback changeStateCB)
	:GameState{ system, changeStateCB }
	, mMouseIsClicked{false}
{
}

void MainMenuState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
}

void MainMenuState::Exit()
{
	mSystem.InputMgr.RemoveObserver(this);
}

void MainMenuState::Update()
{
	//mSystem.GUIMgr.UpdateButtons();
}

void MainMenuState::Draw()
{
	mSystem.RenderMgr.MainMenuRender();
}

void MainMenuState::OnMouseMove(int x, int y)
{
}

void MainMenuState::OnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape) { mSystem.RenderMgr.GetWindow().close(); }
	if (key == sf::Keyboard::P)
	{
		auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel());
		mChangeStateCB(std::move(newState));
	}
}

void MainMenuState::OnKeyRelease(sf::Keyboard::Key key)
{
}

void MainMenuState::OnMouseClick(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = true; }
}

void MainMenuState::OnMouseRelease(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = false; }
}
