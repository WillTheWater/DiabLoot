#include "PlayState.h"
#include "MainMenuState.h"
#include "SoundManager.h"
#include "Core.h"

PlayState::PlayState(System& system, ChangeStateCallback changeStateCB, Level& level)
	:GameState{ system, changeStateCB }
	,mLevel{level}
	, mMouseIsClicked{false}
	, mIsInventoryOpen{false}

{
	mSystem.GUIMgr.GetButton(BUTTONS::NEXT_LEVEL_ID).SetClickCB([this]() {auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel()); mChangeStateCB(std::move(newState)); });
	mSystem.GUIMgr.GetButton(BUTTONS::EXIT_PLAY_ID).SetClickCB([this]() {auto newState = std::make_unique<MainMenuState>(mSystem, mChangeStateCB); mChangeStateCB(std::move(newState)); });
	mSystem.GUIMgr.GetButton(BUTTONS::INVENTORY_ID).SetClickCB([this]() {if (mSystem.InventoryMgr.isOpen()) {mSystem.InventoryMgr.ToggleInventory();} });
	mSystem.GUIMgr.GetButton(BUTTONS::OPEN_INVENTORY_ID).SetClickCB([this]() {{mSystem.InventoryMgr.ToggleInventory();} });
}

void PlayState::Enter()
{
	mSystem.InputMgr.AddObserver(this);
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
	mSystem.GUIMgr.PlayStateUpdate(mMousePosition, mMouseIsClicked);
}

void PlayState::Draw()
{
	mSystem.RenderMgr.RenderLevel(mLevel);
	mSystem.RenderMgr.PlayStateRender();
}

void PlayState::OnMouseMove(int x, int y)
{
	mMousePosition = sf::Vector2f{ (float)x, (float)y };
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
	if (key == sf::Keyboard::S)
	{
		mSystem.InventoryMgr.saveInventory();
	}
	if (key == sf::Keyboard::L)
	{
		mSystem.InventoryMgr.loadInventory();
	}
	if (key == sf::Keyboard::O)
	{
		mSystem.InventoryMgr.sortInventory();
	}
}

void PlayState::OnMouseClick(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = true; }
}

void PlayState::OnMouseRelease(sf::Mouse::Button button)
{
	if (button == sf::Mouse::Left) { mMouseIsClicked = false; }
}
