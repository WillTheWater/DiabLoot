#include "WinState.h"
#include "MainMenuState.h"

WinState::WinState(System& system, ChangeStateCallback changeStateCB, Level& level)
	: GameState{system, changeStateCB}
	, mLevel{level}
	, mMouseIsClicked{false}
{
	mSystem.GUIMgr.GetButton(BUTTONS::NEW_GAME_ID).SetClickCB([this]() { auto newState = std::make_unique<MainMenuState>(mSystem, mChangeStateCB); mChangeStateCB(std::move(newState)); });
}

void WinState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
	mSystem.TimeMgr.LockSpeedRunTime();
	mSystem.FireWorks.StartFireworks();
}

void WinState::Exit()
{
	mSystem.FireWorks.EndFireWorks();
	mSystem.InputMgr.RemoveObserver(this);
}

void WinState::Update()
{
	mSystem.FireWorks.Update(mSystem.TimeMgr.GetDeltaTime());
	mSystem.GUIMgr.PlayStateUpdate(mMousePosition, mMouseIsClicked);
}

void WinState::Draw()
{
	mSystem.RenderMgr.LevelRender(mLevel);
	mSystem.RenderMgr.WinStateRender();
}

void WinState::OnMouseMove(int x, int y)
{
	mMousePosition = sf::Vector2f{ (float)x, (float)y };
}

void WinState::OnKeyPress(sf::Keyboard::Key key)
{
}

void WinState::OnKeyRelease(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::M) { SoundManager::GetInstance().MuteToggle(); }	
}

void WinState::OnMouseClick(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = true; }
}

void WinState::OnMouseRelease(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = false; }
}
