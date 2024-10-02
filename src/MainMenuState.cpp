#include "MainMenuState.h"
#include "PlayState.h"
#include "SoundManager.h"
#include <windows.h>
#include "Core.h"

MainMenuState::MainMenuState(System& system, ChangeStateCallback changeStateCB)
	:GameState{ system, changeStateCB }
	, mMouseIsClicked{false}
{
	// New Game Button || Enter game, clear inventory and level upgrades
	mSystem.GUIMgr.GetButton(BUTTONS::START_ID).SetClickCB([this]() { 
		mSystem.LevelMgr.ResetLevelLoop();
		mSystem.LevelMgr.ResetLevelUpgrades();
		mSystem.InventoryMgr.DeleteInventory();
		mSystem.TimeMgr.StartSpeedRunclock();
		auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel());
		mChangeStateCB(std::move(newState));
		});

	mSystem.GUIMgr.GetButton(BUTTONS::EXIT_ID).SetClickCB([this]() { mSystem.RenderMgr.GetWindow().close(); });
	mSystem.GUIMgr.GetButton(BUTTONS::CLOSE_BUTTON_ID).SetClickCB([this]() { mSystem.RenderMgr.GetWindow().close(); });
	mSystem.GUIMgr.GetButton(BUTTONS::MINI_BUTTON_ID).SetClickCB([this]() {HWND hwnd = mSystem.RenderMgr.GetWindow().getSystemHandle();	ShowWindow(hwnd, SW_MINIMIZE);});
	mSystem.GUIMgr.GetButton(BUTTONS::LOAD_GAME_ID).SetClickCB([this]() { mSystem.Load();
	auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel());
	mChangeStateCB(std::move(newState)); });
	mSystem.GUIMgr.GetButton(BUTTONS::MUTE_BUTTON_ID).SetClickCB([this]() { SoundManager::GetInstance().MuteToggle(); });
}

void MainMenuState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
	SoundManager::GetInstance().PlayMusic(MUSIC::INTRO, 10.f);
	SoundManager::GetInstance().PlayASound(PLAYSOUND::FIRE, 20.f, 1.f, true);
	SoundManager::GetInstance().PlayASound(PLAYSOUND::TOWN, 15.f, 1.f, true);
}

void MainMenuState::Exit()
{
	mSystem.InputMgr.RemoveObserver(this);
	SoundManager::GetInstance().StopMusic(MUSIC::INTRO);
	SoundManager::GetInstance().StartMusicSequence();
}

void MainMenuState::Update()
{
	mSystem.GUIMgr.MainMenuUpdate(mMousePosition, mMouseIsClicked);
}

void MainMenuState::Draw()
{
	mSystem.RenderMgr.MainMenuRender();
	mSystem.RenderMgr.DrawToolTipWarning(mMousePosition);
}

void MainMenuState::OnMouseMove(int x, int y)
{
	mMousePosition = sf::Vector2f{ (float)x, (float)y };
}

void MainMenuState::OnKeyPress(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::Escape) { mSystem.RenderMgr.GetWindow().close(); }
}

void MainMenuState::OnKeyRelease(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::M) { SoundManager::GetInstance().MuteToggle(); }
}

void MainMenuState::OnMouseClick(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = true; }
	
}

void MainMenuState::OnMouseRelease(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = false;	}
}
