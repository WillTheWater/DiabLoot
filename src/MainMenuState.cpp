#include "MainMenuState.h"
#include "PlayState.h"
#include "SoundManager.h"
#include "Core.h"

MainMenuState::MainMenuState(System& system, ChangeStateCallback changeStateCB)
	:GameState{ system, changeStateCB }
	, mMouseIsClicked{false}
{
	mSystem.GUIMgr.GetButton(BUTTONS::START_ID).SetClickCB([this]() {
		auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel());
		mChangeStateCB(std::move(newState));
		});
	mSystem.GUIMgr.GetButton(BUTTONS::EXIT_ID).SetClickCB([this]() { mSystem.RenderMgr.GetWindow().close(); });
	mSystem.GUIMgr.GetButton(BUTTONS::LOAD_GAME_ID).SetClickCB([this]() { mSystem.InventoryMgr.loadInventory();
	mSystem.LevelMgr.LoadLevels();
	auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel());
	mChangeStateCB(std::move(newState)); });
}

void MainMenuState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
	SoundManager::GetInstance().PlayMusic(MUSIC::INTRO);
	SoundManager::GetInstance().StopMusic(MUSIC::TRISTRAM); 
}

void MainMenuState::Exit()
{
	mSystem.InputMgr.RemoveObserver(this);
	SoundManager::GetInstance().StopMusic(MUSIC::INTRO);
}

void MainMenuState::Update()
{
	mSystem.GUIMgr.MainMenuUpdate(mMousePosition, mMouseIsClicked);
}

void MainMenuState::Draw()
{
	mSystem.RenderMgr.MainMenuRender();
}

void MainMenuState::OnMouseMove(int x, int y)
{
	mMousePosition = sf::Vector2f{ (float)x, (float)y };
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
	if (button == sf::Mouse::Left) { mMouseIsClicked = false;	}
}
