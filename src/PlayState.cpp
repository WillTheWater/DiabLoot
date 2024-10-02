#include "PlayState.h"
#include "MainMenuState.h"
#include "WinState.h"
#include "SoundManager.h"
#include <windows.h>
#include "Core.h"

PlayState::PlayState(System& system, ChangeStateCallback changeStateCB, Level& level)
	:GameState{ system, changeStateCB }
	,mLevel{level}
	, mMouseIsClicked{false}
	, mIsInventoryOpen{false}
	, mHasWon{false}
{
	mSystem.GUIMgr.GetButton(BUTTONS::NEXT_LEVEL_ID).SetClickCB([this]() {auto newState = std::make_unique<PlayState>(mSystem, mChangeStateCB, mSystem.LevelMgr.GetNextLevel()); mChangeStateCB(std::move(newState)); });
	mSystem.GUIMgr.GetButton(BUTTONS::EXIT_PLAY_ID).SetClickCB([this]() {mSystem.LevelMgr.SaveLevels(); mSystem.InventoryMgr.SaveInventory(); auto newState = std::make_unique<MainMenuState>(mSystem, mChangeStateCB); mChangeStateCB(std::move(newState)); });
	mSystem.GUIMgr.GetButton(BUTTONS::INVENTORY_ID).SetClickCB([this]() {if (mSystem.InventoryMgr.IsOpen()) {mSystem.InventoryMgr.ToggleInventory();} });
	mSystem.GUIMgr.GetButton(BUTTONS::OPEN_INVENTORY_ID).SetClickCB([this]() {mSystem.InventoryMgr.ToggleInventory();});
	mSystem.GUIMgr.GetButton(BUTTONS::INFO_BUTTON_ID).SetClickCB([this]() {mSystem.InventoryMgr.ToggleItemMissingList();});

	mSystem.GUIMgr.GetButton(BUTTONS::SORT_BUTTON_ID).SetClickCB([this]() { mSystem.InventoryMgr.SortInventory(); });
	mSystem.GUIMgr.GetButton(BUTTONS::CLOSE_BUTTON_ID).SetClickCB([this]() { mSystem.RenderMgr.GetWindow().close(); });

	mSystem.GUIMgr.GetButton(BUTTONS::MINI_BUTTON_ID).SetClickCB([this]() {HWND hwnd = mSystem.RenderMgr.GetWindow().getSystemHandle();	ShowWindow(hwnd, SW_MINIMIZE); });
	mSystem.GUIMgr.GetButton(BUTTONS::UPGRADE_BUTTON_ID).SetClickCB([this]() {this->UpgradeLevel(); });
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
	mSystem.TimeMgr.PrintTimeStats();
	bool hasWon = false;
	if (mSystem.InventoryMgr.HasOneOfEverything())
	{	
		hasWon = true;
	}

	mLevel.UpdateLevel();
	mSystem.GUIMgr.PlayStateUpdate(mMousePosition, mMouseIsClicked);
	if (hasWon)
	{
		auto newState = std::make_unique<WinState>(mSystem, mChangeStateCB, mLevel);
		mChangeStateCB(std::move(newState));
	}
}

void PlayState::Draw()
{
	mSystem.RenderMgr.LevelRender(mLevel);
	mSystem.RenderMgr.PlayStateRender();
	mSystem.RenderMgr.DrawToolTip(mMousePosition);
	mSystem.RenderMgr.ItemsMissingListRender();
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
	if (key == sf::Keyboard::Escape)
	{
		if (mSystem.InventoryMgr.IsOpen()) { mSystem.InventoryMgr.ToggleInventory(); }
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
		mSystem.LevelMgr.SaveLevels();
		mSystem.InventoryMgr.SaveInventory();
	}
	if (key == sf::Keyboard::L)
	{
		mSystem.LevelMgr.LoadLevels();
		mLevel.DeactiveChests();	// This is just to simulate loading the level
		mLevel.ActivateChests();    // This is just to simulate loading the level
		mSystem.InventoryMgr.LoadInventory();
	}
	if (key == sf::Keyboard::O)
	{
		mSystem.InventoryMgr.SortInventory();
	}
	if (key == sf::Keyboard::D)
	{
		mSystem.InventoryMgr.DeleteInventory();
	}
	if (key == sf::Keyboard::U)
	{
		UpgradeLevel();
	}
	if (key == sf::Keyboard::M) { SoundManager::GetInstance().MuteToggle(); }
	if (key == sf::Keyboard::C)
	{
		mSystem.InventoryMgr.DebugGetOneOfEverything();
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

void PlayState::UpgradeLevel()
{
	if (mLevel.GetUpgradeLevel() == LEVELS::MAX_UPGRADES - 1)
	{
		return;
	}
	int cost = mSystem.AssetMgr.GetCostForNextLevelUpgrade(mLevel.GetUpgradeLevel());
	if (mSystem.InventoryMgr.GetGold() < cost)
	{
		return;
	}
	mSystem.InventoryMgr.RemoveGold(cost);
	mLevel.UpgradeLevel();
}
